#include <base/log.h>

#include <stdio.h> /* @@debug */
#include "app.h"

extern "C"
void genode_log(const char* message) {
    Genode::log(message);
}

extern "C"
int genode_sandbox_apply_config(char *context, char const *text)
{
    fprintf(stderr, "genode_sandbox_apply_config(%p, %s)\n", context, text);
    // App::HasSandbox *app = reinterpret_cast<App::HasSandbox *>(context);
    App::HasSandbox *app = theApp;
    fprintf(stderr, "got app %p@@\n", app);
    try {
        Genode::Xml_node config(text);
        fprintf(stderr, "config tag type: %s\n", config.type().string());
        app->applyConfig(config);
        return 0;
    }
    catch (Genode::Xml_node::Invalid_syntax) {
        fprintf(stderr, "@@Invalid_syntax\n");
        return -1;
    }
}