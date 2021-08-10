#include <base/log.h>

extern "C"
void genode_log(const char* message) {
    Genode::log(message);
}