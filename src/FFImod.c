#include "xs.h"

extern int stuff();

void xs_fun(xsMachine *the)
{
    xsResult = xsInteger(stuff());
}
