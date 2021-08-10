/* Genode includes */
#include <libc/component.h>

/* libc includes */
#include <stdlib.h> /* 'exit'   */

extern char **genode_argv;
extern int    genode_argc;
extern char **genode_envp;

/* provided by the application */
extern "C" int main(int argc, char ** argv, char **envp);

static char** no_args = {};
static char** no_env = {};

static void construct_component(Libc::Env &env)
{
    using Genode::Xml_node;

    env.config([&] (Xml_node const &node) {
        // never mind args, env for now
        genode_argc = 0;
        genode_argv = no_args;
        genode_envp = no_env;
    });
    exit(main(genode_argc, genode_argv, genode_envp));
}

void Libc::Component::construct(Libc::Env &env)
{
	Libc::with_libc([&] () { construct_component(env); });
}
