#include "xs.h"

// see FFIgenode.cpp
extern void genode_log();
extern int genode_sandbox_apply_config(char* context, const char *text);

void xs_fun(xsMachine *the)
{
    const char* message = xsToString(xsArg(0));
    genode_log(message);
}

static void *getSandbox(xsMachine *the)
{
	void *result = xsGetHostData(xsThis);
	if (!result)
		xsUnknownError("no sandbox host data");
	return result;
}

void applyConfig(xsMachine *the)
{
    fprintf(stderr, "applyConfig...\n");
    void *sandbox = getSandbox(the);
    fprintf(stderr, "applyConfig sandbox: %p\n", sandbox);
    const char* text = xsToString(xsArg(0));
    fprintf(stderr, "applyConfig sandbox config text: %s\n", text);
    const int err = genode_sandbox_apply_config(sandbox, text);
    fprintf(stderr, "applyConfig err: %d\n", err);
    if (err != 0) {
        xsUnknownError("bad config %s", text);
    }
}