# goa-hello: toward JavaScript on genode using Moddable XS

I started with the hello package from then [Nov 2019 article
introducing goa](https://genodians.org/nfeske/2019-11-25-goa).

Then I grabbed the
[helloworld](https://github.com/Moddable-OpenSource/moddable/tree/public/examples/helloworld)
example from the Moddable XS SDK, generated C sources, and got it to
build.

Then I worked out getting `goa run` to work. My `artifacts` is
a bit of a kludge: it reaches out from `var/build` back to `src/bin`.


## Respin

```
make -C src respin && goa build
```

or for debugging:

```
make -C src respin && goa build --verbose --jobs 1
```
