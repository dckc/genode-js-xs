#include <base/log.h>
#include <base/component.h>
#include <libc/component.h>

#include <stdio.h>

extern "C" int main(int argc, const char* argv[]);

void Libc::Component::construct(Libc::Env &env)
{
  Genode::log("Hello before libc");
  Libc::with_libc([&] () {
      printf("hello via stdio\n");
      Genode::log("Hello in libc");
      const char *argv[] = {"genode_main"};
      main(1, argv);
    });
}
