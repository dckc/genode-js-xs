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
[init -> genode-js-xs] Hello, world - sample
[init -> genode-js-xs] 
[init -> genode-js-xs] 123
[init] child "genode-js-xs" exited with exit value 0
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
export PATH=vendor/goa/bin:$PATH
```

Then apply `vendor/moddable-xst.patch`. (see
[issues/8](https://github.com/dckc/genode-js-xs/issues/8)).


When we `goa build`, we see some harmless compiler warnings from XS.
And we get linker warnings (see [Issue \#9](https://github.com/dckc/genode-js-xs/issues/9)).

```
genode-js-xs$ goa build
download nfeske/api/base/2021-02-22.tar.xz
download nfeske/api/base/2021-02-22.tar.xz.sig
download nfeske/api/libc/2021-02-22.tar.xz
download nfeske/api/libc/2021-02-22.tar.xz.sig
download nfeske/api/posix/2020-05-17.tar.xz
download nfeske/api/posix/2020-05-17.tar.xz.sig
[genode-js-xs:make] BUILD_DIR=/home/connolly/projects/genode-js-xs/var/build/x86_64
[genode-js-xs:make] MODDABLE=/home/connolly/projects/genode-js-xs/vendor/moddable
make[1]: warning: jobserver unavailable: using -j1.  Add '+' to parent make rule.
[genode-js-xs:make] # xst debug : cc xsAll.c
genode-x86-gcc: warning: .../libgcc.a: linker input file unused because linking not done
[genode-js-xs:make] # xst debug : cc xsAPI.c
...
.../vendor/moddable/xs/tools/yaml/api.c:1147:7: warning: variable ‘context’ set but not used [-Wunused-but-set-variable]
     } context;
       ^~~~~~~
...
[genode-js-xs:make] # xst release : cc xst
```

The first `goa run` involves downloading various genode archives:

```
connolly@jambox:~/projects/genode-js-xs$ goa run
[genode-js-xs:make] BUILD_DIR=/home/connolly/projects/genode-js-xs/var/build/x86_64
[genode-js-xs:make] MODDABLE=/home/connolly/projects/genode-js-xs/vendor/moddable
make[1]: warning: jobserver unavailable: using -j1.  Add '+' to parent make rule.
download nfeske/bin/x86_64/base-linux/2021-06-08.tar.xz
download nfeske/bin/x86_64/base-linux/2021-06-08.tar.xz.sig
download nfeske/bin/x86_64/init/2021-02-22.tar.xz
download nfeske/bin/x86_64/init/2021-02-22.tar.xz.sig
download nfeske/bin/x86_64/libc/2021-02-22.tar.xz
download nfeske/bin/x86_64/libc/2021-02-22.tar.xz.sig
download nfeske/bin/x86_64/posix/2021-02-22.tar.xz
download nfeske/bin/x86_64/posix/2021-02-22.tar.xz.sig
download nfeske/bin/x86_64/vfs/2021-02-22.tar.xz
download nfeske/bin/x86_64/vfs/2021-02-22.tar.xz.sig
download nfeske/src/base-linux/2021-06-08.tar.xz
download nfeske/src/base-linux/2021-06-08.tar.xz.sig
download nfeske/src/init/2021-02-22.tar.xz
download nfeske/src/init/2021-02-22.tar.xz.sig
download nfeske/src/libc/2021-02-22.tar.xz
download nfeske/src/libc/2021-02-22.tar.xz.sig
download nfeske/src/posix/2021-02-22.tar.xz
download nfeske/src/posix/2021-02-22.tar.xz.sig
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
[init -> genode-js-xs] Hello, world - sample
[init -> genode-js-xs] 
[init -> genode-js-xs] 123
[init] child "genode-js-xs" exited with exit value 0
```
