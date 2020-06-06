# goa-hello: toward JavaScript on genode using Moddable XS

It works like this, once it's built (see below):

```
goa-hello$ goa run
[goa-hello:make] recursive make: make
Genode 20.02-1-gac1b2ec24e
17592186044415 MiB RAM and 8997 caps assigned to init
[init -> goa-hello] Hello before libc
[init -> goa-hello] hello via stdio
[init -> goa-hello] Hello in libc
[init -> goa-hello] lin_xs_cli: loading top-level main.js
[init -> goa-hello]  lin_xs_cli: loaded
[init -> goa-hello] lin_xs_cli: invoking main(argv)
[init -> goa-hello] Hello, world - sample
[init -> goa-hello] main() returned immediate value (not a promise). exiting
[init -> goa-hello] Warning: rtc not configured, returning 0
Warning: blocking canceled in entrypoint constructor
[init] child "goa-hello" exited with exit value 0
```

I started with the hello package from then [Nov 2019 article
introducing goa](https://genodians.org/nfeske/2019-11-25-goa).

Then I grabbed the
[helloworld](https://github.com/Moddable-OpenSource/moddable/tree/public/examples/helloworld)
example from the Moddable XS SDK, generated C sources, and got it to
build.

Then I worked out getting `goa run` to work. My `artifacts` is
a bit of a kludge: it reaches out from `var/build` back to `src/bin`.

## before `goa build`: `gensrc`, `genode_platform`

There's a bit of an impedence mismatch between `goa build` and the
[Moddable SDK](https://github.com/Moddable-OpenSource/moddable/), so
use `make -C src gensrc` to generate C etc. before running `goa
build`.

We also extend the Moddable SDK to add a `genode` platform
using `make -C src genode_platform`.


## Respin workflow

The several layers of build directories and makefiles means the
dependencies are easy to get out of date, so the `respin`
target does `realclean` before the rest:

```
make -C src respin && goa build
```

or for debugging:

```
make -C src respin && goa build --verbose --jobs 1
```
