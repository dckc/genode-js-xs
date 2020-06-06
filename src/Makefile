MODDABLE=~/projects/moddable
VERBOSE=0

# `goa build` sets up all sorts of CPPFLAGS (-I...) and such; pass them to the xs makefile
# https://www.gnu.org/software/make/manual/html_node/Variables_002fRecursion.html#Variables_002fRecursion
export CPPFLAGS CFLAGS LDFLAGS LDLIBS CXX CC VERBOSE

XS_GENSRC=./tmp/genode/debug/src
build:
	echo recursive make: $(MAKE)
	MODDABLE=$(MODDABLE) $(MAKE) -e -C $(XS_GENSRC) NAME=goa-hello

HERE=$(shell /bin/pwd)

# Generate C code etc. for hello world xs app.
gensrc: $(XS_GENSRC)/makefile
$(XS_GENSRC)/makefile: $(MODDABLE)/.envrc manifest.json
	. $(MODDABLE)/.envrc && mcconfig -p genode -d -o .
	make -C $(XS_GENSRC) genode.c wasm_xs.c xs_link

# add the genode platform to the Moddable SDK
genode_platform: $(MODDABLE)/xs/platforms/genode.c \
			$(MODDABLE)/xs/platforms/genode_main.cc \
			$(MODDABLE)/tools/mcconfig/make.genode.mk
$(MODDABLE)/xs/platforms/genode.c: xs_platform/genode.c
	cp $< $@
$(MODDABLE)/xs/platforms/genode_main.cc: xs_platform/genode_main.cc
	cp $< $@
$(MODDABLE)/tools/mcconfig/make.genode.mk: xs_platform/make.genode.mk
	cp $< $@

clean:
	rm -rf var/build/x86_64/tmp

respin: realclean genode_platform gensrc

realclean: clean
	rm -rf bin tmp
	rm -rf ~/projects/moddable/build/tmp
	rm -f $(MODDABLE)/xs/platforms/genode*.*
	rm -f $(MODDABLE)/tools/mcconfig/make.genode.mk
