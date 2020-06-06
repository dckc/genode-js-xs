MODDABLE=~/projects/moddable
VERBOSE=0

# `goa build` sets up all sorts of CPPFLAGS (-I...) and such; pass them to the xs makefile
# https://www.gnu.org/software/make/manual/html_node/Variables_002fRecursion.html#Variables_002fRecursion
export CPPFLAGS CFLAGS LDFLAGS LDLIBS CXX CC VERBOSE

XS_GENSRC=./tmp/genode/debug/helloworld
build:
	echo recursive make: $(MAKE)
	MODDABLE=$(MODDABLE) $(MAKE) -e -C $(XS_GENSRC) NAME=goa-hello

HERE=$(shell /bin/pwd)

gensrc: $(XS_GENSRC)/makefile
$(XS_GENSRC)/makefile: $(MODDABLE)/.envrc $(MODDABLE)/examples/helloworld/manifest.json
	. $(MODDABLE)/.envrc && cd $(MODDABLE)/examples/helloworld && \
		mcconfig -p genode -d -o $(HERE)/src
	cd $(HERE)/src && make -C $(XS_GENSRC) genode.c xs_link

clean:
	rm -rf var/build/x86_64/tmp

respin: realclean gensrc

realclean: clean
	rm -rf bin tmp
	rm -rf ~/projects/moddable/build/tmp
