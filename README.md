# Toward JavaScript on genode using Moddable XS

To run `src/main.js` using [xst][] from the [Moddable SDK][sdk],
we `goa build` (see below) and then:

```
genode-js-xs$ goa run
[genode-js-xs:make] BUILD_DIR=/home/connolly/projects/genode-js-xs/var/build/x86_64
[genode-js-xs:make] MODDABLE=/home/connolly/projects/genode-js-xs/vendor/moddable
make[1]: warning: jobserver unavailable: using -j1.  Add '+' to parent make rule.
[genode-js-xs:make] # xsl modules
### 572 instances, 453 keys, 61 colors, 20 holes
Genode 20.02-1-gac1b2ec24e
17592186044415 MiB RAM and 8997 caps assigned to init
[init -> genode-js-xs] Hello, world - sample
[init -> genode-js-xs] Warning: rtc not configured, returning 0
[init -> genode-js-xs] dog says bark
Warning: blocking canceled in entrypoint constructor
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

When we `goa build`, we see some harmless compiler warnings from XS.

```
genode-js-xs$ goa build
download nfeske/api/base/2020-02-27.tar.xz
download nfeske/api/base/2020-02-27.tar.xz.sig
...
[genode-js-xs:make] BUILD_DIR=/home/connolly/projects/genode-js-xs/var/build/x86_64
[genode-js-xs:make] MODDABLE=/home/connolly/projects/genode-js-xs/vendor/moddable
make[1]: warning: jobserver unavailable: using -j1.  Add '+' to parent make rule.
[genode-js-xs:make] # xsc main.xsb
[genode-js-xs:make] # cc xsArguments.c
[genode-js-xs:make] # cc xsArray.c
...
[genode-js-xs:make] # xsl modules
/home/connolly/projects/genode-js-xs/vendor/moddable/xs/sources/xsDebug.c:2211:20: warning: ‘xsInstrumentUnits’ defined but not used [-Wunused-const-variable=]
 static char* const xsInstrumentUnits[xsInstrumentCount] ICACHE_XS6STRING_ATTR = {
                    ^~~~~~~~~~~~~~~~~
...
### 572 instances, 453 keys, 61 colors, 20 holes
### 572 instances, 453 keys, 61 colors, 20 holes
Total resource size: 0 bytes
[genode-js-xs:make] # cc genode.c
[genode-js-xs:make] # cc mc.resources.c
[genode-js-xs:make] # cc mc.xs.c
...
[genode-js-xs:make] # cc hello
```

The first `goa run` involves downloading various genode archives:

```
genode-js-xs$ goa run
[genode-js-xs:make] BUILD_DIR=/home/connolly/projects/genode-js-xs/var/build/x86_64
[genode-js-xs:make] MODDABLE=/home/connolly/projects/genode-js-xs/vendor/moddable
make[1]: warning: jobserver unavailable: using -j1.  Add '+' to parent make rule.
download nfeske/bin/x86_64/base-linux/2020-02-27.tar.xz
download nfeske/bin/x86_64/base-linux/2020-02-27.tar.xz.sig
download nfeske/bin/x86_64/init/2020-02-27.tar.xz
download nfeske/bin/x86_64/init/2020-02-27.tar.xz.sig
download nfeske/bin/x86_64/libc/2020-02-27.tar.xz
download nfeske/bin/x86_64/libc/2020-02-27.tar.xz.sig
download nfeske/bin/x86_64/posix/2020-02-27.tar.xz
download nfeske/bin/x86_64/posix/2020-02-27.tar.xz.sig
download nfeske/bin/x86_64/vfs/2020-02-27.tar.xz
download nfeske/bin/x86_64/vfs/2020-02-27.tar.xz.sig
download nfeske/src/base-linux/2020-02-27.tar.xz
download nfeske/src/base-linux/2020-02-27.tar.xz.sig
download nfeske/src/init/2020-02-27.tar.xz
download nfeske/src/init/2020-02-27.tar.xz.sig
download nfeske/src/libc/2020-02-27.tar.xz
download nfeske/src/libc/2020-02-27.tar.xz.sig
download nfeske/src/posix/2020-02-27.tar.xz
download nfeske/src/posix/2020-02-27.tar.xz.sig
download nfeske/src/vfs/2020-02-27.tar.xz
download nfeske/src/vfs/2020-02-27.tar.xz.sig
download nfeske/api/block_session/2020-02-27.tar.xz
download nfeske/api/block_session/2020-02-27.tar.xz.sig
download nfeske/api/file_system_session/2019-11-18.tar.xz
download nfeske/api/file_system_session/2019-11-18.tar.xz.sig
download nfeske/api/os/2020-02-27.tar.xz
download nfeske/api/os/2020-02-27.tar.xz.sig
download nfeske/api/report_session/2019-02-25.tar.xz
download nfeske/api/report_session/2019-02-25.tar.xz.sig
download nfeske/api/rtc_session/2019-08-20.tar.xz
download nfeske/api/rtc_session/2019-08-20.tar.xz.sig
download nfeske/api/so/2019-02-25.tar.xz
download nfeske/api/so/2019-02-25.tar.xz.sig
download nfeske/api/terminal_session/2019-02-25.tar.xz
download nfeske/api/terminal_session/2019-02-25.tar.xz.sig
download nfeske/api/timer_session/2019-11-25.tar.xz
download nfeske/api/timer_session/2019-11-25.tar.xz.sig
download nfeske/api/vfs/2020-02-27.tar.xz
download nfeske/api/vfs/2020-02-27.tar.xz.sig
Genode 20.02-1-gac1b2ec24e
17592186044415 MiB RAM and 8997 caps assigned to init
[init -> genode-js-xs] Hello, world - sample
[init -> genode-js-xs] Warning: rtc not configured, returning 0
[init -> genode-js-xs] dog says bark
Warning: blocking canceled in entrypoint constructor
[init] child "genode-js-xs" exited with exit value 0
```
