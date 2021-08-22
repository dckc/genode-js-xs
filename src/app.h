#ifndef __APP__
#define __APP__
#include <util/xml_node.h>


namespace App {
    using namespace Genode;

    struct HasSandbox {
        virtual void show(const char *message) = 0;
        virtual void applyConfig(Xml_node const &config) = 0;
    };
}

extern App::HasSandbox *theApp;

#endif
