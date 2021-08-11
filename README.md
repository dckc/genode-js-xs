# Toward JavaScript on genode using Moddable XS

To run `src/main.js` using [xst][] from the [Moddable SDK][sdk],
we `goa build` (see below) and then:

```
genode-js-xs$ goa run
[genode-js-xs:make] BUILD_DIR=/home/connolly/projects/genode-js-xs/var/build/x86_64
[genode-js-xs:make] MODDABLE=/home/connolly/projects/genode-js-xs/vendor/moddable
make[1]: warning: jobserver unavailable: using -j1.  Add '+' to parent make rule.
Genode sculpt-21.03-24-g704bd0695f8 <local changes>
17592186044415 MiB RAM and 8997 caps assigned to init
[init -> genode-js-xs] parent provides
[init -> genode-js-xs]   service "ROM"
[init -> genode-js-xs]   service "LOG"
[init -> genode-js-xs]   service "RM"
[init -> genode-js-xs]   service "CPU"
[init -> genode-js-xs]   service "PD"
[init -> genode-js-xs]   service "Timer"
[init -> genode-js-xs] child "hello"
[init -> genode-js-xs]   RAM quota:  204552K
[init -> genode-js-xs]   cap quota:  66
[init -> genode-js-xs]   ELF binary: hello
[init -> genode-js-xs]   priority:   0
[init -> genode-js-xs -> hello] Hello, world - sample
[init -> genode-js-xs -> hello] dog says bark
[init -> genode-js-xs -> hello] genode logging:
[init -> genode-js-xs -> hello] js to genode
[init -> genode-js-xs] child "hello" exited with exit value 0
Expect: 'interact' received 'strg+c' and was cancelled
```

[xst]: https://github.com/Moddable-OpenSource/moddable/blob/public/documentation/xs/xst.md
[sdk]: https://github.com/Moddable-OpenSource/moddable#readme

## Background: `goa build`

 - [Goa \- streamlining the development of Genode applications](https://genodians.org/nfeske/2019-11-25-goa)  
   Nov 2019 by Norman Feske
   - live coding: [JavaScript on the Genode Microkernel OS, part 1: hello genode \- Twitch](https://www.twitch.tv/videos/1090280743)
     - 1st 7 min: live coding
     - second half: a bit of explanation.

## Building from source

To get `vendor/goa` and `vendor/moddable`:

```sh
git submodule update
export PATH=$PWD/vendor/goa/bin:$PATH
```

When we `goa build`, we see some harmless compiler warnings from XS.

```
genode-js-xs$ goa build
download nfeske/api/base/2021-02-22.tar.xz
download nfeske/api/base/2021-02-22.tar.xz.sig
download nfeske/api/libc/2021-02-22.tar.xz
download nfeske/api/libc/2021-02-22.tar.xz.sig
[genode-js-xs:make] BUILD_DIR=/home/connolly/projects/genode-js-xs/var/build/x86_64
[genode-js-xs:make] MODDABLE=/home/connolly/projects/genode-js-xs/vendor/moddable
make[1]: warning: jobserver unavailable: using -j1.  Add '+' to parent make rule.
[genode-js-xs:make] # xsc FFI.xsb
[genode-js-xs:make] # xsc main.xsb
[genode-js-xs:make] # xsid FFIgenode.cpp.xsi
[genode-js-xs:make] # cc xsAll.c
[genode-js-xs:make] # cc xsDataView.c
[genode-js-xs:make] # cc xsArguments.c
...
[genode-js-xs:make] # cc xsType.c
[genode-js-xs:make] # xsl modules
/home/connolly/projects/genode-js-xs/vendor/moddable/xs/sources/xsAPI.c: In function ‘fxToUnsigned’:
/home/connolly/projects/genode-js-xs/vendor/moddable/xs/sources/xsAPI.c:371:25: warning: this statement may fall through [-Wimplicit-fallthrough=]
   theSlot->value.number = theSlot->value.integer;
   ~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
[genode-js-xs:make] # cc FFIgenode.cpp.o
[genode-js-xs:make] # cc FFImod.c.o
[genode-js-xs:make] # cc mc.xs.c
[genode-js-xs:make] # cc genode.c
[genode-js-xs:make] # cc hello
```

The first `goa run` involves downloading various genode archives:

```

(base) ~/projects/genode-js-xs
20:24 connolly@jambox$ goa run
[genode-js-xs:make] BUILD_DIR=/home/connolly/projects/genode-js-xs/var/build/x86_64
[genode-js-xs:make] MODDABLE=/home/connolly/projects/genode-js-xs/vendor/moddable
make[1]: warning: jobserver unavailable: using -j1.  Add '+' to parent make rule.
download nfeske/bin/x86_64/base-linux/2021-06-08.tar.xz
download nfeske/bin/x86_64/base-linux/2021-06-08.tar.xz.sig
download nfeske/bin/x86_64/init/2021-02-22.tar.xz
download nfeske/bin/x86_64/init/2021-02-22.tar.xz.sig
download nfeske/bin/x86_64/libc/2021-02-22.tar.xz
download nfeske/bin/x86_64/libc/2021-02-22.tar.xz.sig
download nfeske/bin/x86_64/vfs/2021-02-22.tar.xz
download nfeske/bin/x86_64/vfs/2021-02-22.tar.xz.sig
download nfeske/src/base-linux/2021-06-08.tar.xz
download nfeske/src/base-linux/2021-06-08.tar.xz.sig
download nfeske/src/init/2021-02-22.tar.xz
download nfeske/src/init/2021-02-22.tar.xz.sig
download nfeske/src/libc/2021-02-22.tar.xz
download nfeske/src/libc/2021-02-22.tar.xz.sig
download nfeske/src/vfs/2021-02-22.tar.xz
download nfeske/src/vfs/2021-02-22.tar.xz.sig
download nfeske/api/block_session/2020-05-26.tar.xz
download nfeske/api/block_session/2020-05-26.tar.xz.sig
download nfeske/api/file_system_session/2020-05-26.tar.xz
download nfeske/api/file_system_session/2020-05-26.tar.xz.sig
download nfeske/api/os/2021-02-22.tar.xz
download nfeske/api/os/2021-02-22.tar.xz.sig
download nfeske/api/report_session/2020-03-25.tar.xz
download nfeske/api/report_session/2020-03-25.tar.xz.sig
download nfeske/api/rtc_session/2020-03-25.tar.xz
download nfeske/api/rtc_session/2020-03-25.tar.xz.sig
download nfeske/api/so/2020-05-17.tar.xz
download nfeske/api/so/2020-05-17.tar.xz.sig
download nfeske/api/terminal_session/2020-04-16.tar.xz
download nfeske/api/terminal_session/2020-04-16.tar.xz.sig
download nfeske/api/timer_session/2020-10-08.tar.xz
download nfeske/api/timer_session/2020-10-08.tar.xz.sig
download nfeske/api/vfs/2020-11-26.tar.xz
download nfeske/api/vfs/2020-11-26.tar.xz.sig
Genode sculpt-21.03-24-g704bd0695f8 <local changes>
17592186044415 MiB RAM and 8997 caps assigned to init
[init -> genode-js-xs] parent provides
[init -> genode-js-xs]   service "ROM"
[init -> genode-js-xs]   service "LOG"
[init -> genode-js-xs]   service "RM"
[init -> genode-js-xs]   service "CPU"
[init -> genode-js-xs]   service "PD"
[init -> genode-js-xs]   service "Timer"
[init -> genode-js-xs] child "hello"
[init -> genode-js-xs]   RAM quota:  204552K
[init -> genode-js-xs]   cap quota:  66
[init -> genode-js-xs]   ELF binary: hello
[init -> genode-js-xs]   priority:   0
[init -> genode-js-xs -> hello] Hello, world - sample
[init -> genode-js-xs -> hello] dog says bark
[init -> genode-js-xs -> hello] genode logging:
[init -> genode-js-xs -> hello] js to genode
[init -> genode-js-xs] child "hello" exited with exit value 0
Expect: 'interact' received 'strg+c' and was cancelled

```
