#include "xs.h"

// see FFIgenode.cpp
extern void genode_log();

void xs_fun(xsMachine *the)
{
    const char* message = xsToString(xsArg(0));
    genode_log(message);
}
