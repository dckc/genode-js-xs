/* Genode includes */
#include <libc/component.h>
#include <log_session/log_session.h>
#include <base/session_object.h>
#include <os/buffered_xml.h>
#include <os/sandbox.h>

/* libc includes */
#include <stdlib.h> /* 'exit'   */
#include <stdio.h> /*@@debug fprintf*/

#include "app.h"

extern char **genode_argv;
extern int genode_argc;
extern char **genode_envp;

/* provided by the application */
extern "C" int main(int argc, char **argv, char **envp);

static char **no_env = {};

namespace App
{

    using namespace Genode;

    struct Log_session_component;
    struct Main;
} // namespace App

struct App::Log_session_component : Session_object<Log_session>
{
    template <typename... ARGS>
    Log_session_component(ARGS &&... args) : Session_object(args...) {}

    void write(String const &msg) override
    {
        /* omit line break and zero termination supplied by 'msg' */
        if (msg.size() > 1)
            log("local LOG service: ", Cstring(msg.string(), msg.size() - 2));
    }
};

struct App::Main : Sandbox::Local_service_base::Wakeup, App::HasSandbox
{
    Env &_env;

    Heap _heap{_env.ram(), _env.rm()};

    struct State_handler : Sandbox::State_handler
    {
        void handle_sandbox_state() override {}

    } _state_handler{};

    Sandbox _sandbox{_env, _state_handler};

    typedef Sandbox::Local_service<Log_session_component> Log_service;

    Log_service _log_service{_sandbox, *this};

    void _generate_sandbox_config(Xml_generator &xml) const
    {
        xml.node("parent-provides", [&]() {
            auto service_node = [&](char const *name) { xml.node("service", [&]() { xml.attribute("name", name); }); };

            service_node("ROM");
            service_node("CPU");
            service_node("PD");
            service_node("LOG");
        });
    }

    /**
	 * Sandbox::Local_service_base::Wakeup interface
	 */
    void wakeup_local_service() override
    {
        _log_service.for_each_requested_session([&](Log_service::Request &request) {
            Log_session_component &session = *new (_heap)
                                                 Log_session_component(_env.ep(),
                                                                       request.resources,
                                                                       request.label,
                                                                       request.diag);

            request.deliver_session(session);
        });

        _log_service.for_each_upgraded_session([&](Log_session_component &,
                                                   Session::Resources const &amount) {
            log("received RAM upgrade of ", amount.ram_quota);
            return Log_service::Upgrade_response::CONFIRMED;
        });

        _log_service.for_each_session_to_close([&](Log_session_component &session) {
            destroy(_heap, &session);
            return Log_service::Close_response::CLOSED;
        });
    }

    void show(const char *message) override
    {
        log(message);
    }

    void applyConfig(Xml_node const &config) override
    {
        fprintf(stderr, "applyConfig()\n");
        _sandbox.apply_config(config);
    }

    Main(Env &env) : _env(env)
    {
        log("hello, world!@@@");
        Buffered_xml const config{_heap, "config", [&](Xml_generator &xml) { _generate_sandbox_config(xml); }};

        config.with_xml_node([&](Xml_node const &config) {
            log("generated config: ", config);

            _sandbox.apply_config(config);
        });
        log("sandbox config applied@@@");
    }
};

App::HasSandbox *theApp;

static int construct_component(Libc::Env &env, App::Main &app)
{
    using Genode::Xml_node;

    env.config([&](Xml_node const &node) {
        // Squeeze app pointer thru argv
        genode_argc = -1;
        fprintf(stderr, "app: %p\n", &app);
        static char *the_args[] = {reinterpret_cast<char*>(&app)};
        theApp = &app;
        genode_argv = (char**)the_args;
        genode_envp = no_env;
    });
    return main(genode_argc, genode_argv, genode_envp);
}

void Libc::Component::construct(Libc::Env &env)
{
    App::Main app(env);

    Libc::with_libc([&]() {
        app.show("@@construct!");
        int result = construct_component(env, app);
        app.show("@@print!");
        exit(result);
    });
}
