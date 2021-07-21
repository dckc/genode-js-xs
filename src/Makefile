BUILD_DIR=$(realpath .)
MODDABLE=$(realpath $(BUILD_DIR)/../../../vendor/moddable)
VERBOSE=1
PLATFORM=lin
GOAL=debug

# avoid setting mxMacOSX=1 by default, which results in:
# xsString.c:42:11: fatal error: CoreServices/CoreServices.h: No such file or directory
HINTS = -Dlinux=1

# `goa build` sets up all sorts of CPPFLAGS (-I...) and such; pass them to the xs makefile
# https://www.gnu.org/software/make/manual/html_node/Variables_002fRecursion.html#Variables_002fRecursion
export CPPFLAGS LIB_SRC CFLAGS LDFLAGS LDLIBS CXX CC VERBOSE GOAL BUILD_DIR MODDABLE

# target is $(BUILD_DIR)/bin/$(PLATFORM)/$(GOAL)/xst
# but this Makefile doesn't know the dependencies,
# so always use the xs makefile.

# passing CPPFLAGS and such via `make CC=...` seems awkward
# but it was the only way I could get it to work.

# See also ../vendor/moddable-xst.patch
# for changes to LIBRARIES, LINK_OPTIONS

build:
	@echo BUILD_DIR=$(BUILD_DIR)
	@echo MODDABLE=$(MODDABLE)
	make -C $(MODDABLE)/xs/makefiles/$(PLATFORM) \
		CC="$(CC) $(CPPFLAGS) $(HINTS) $(LDFLAGS) $(LDLIBS)"

what-env-might-help:
	env | grep genode-js-xs

clean:
	rm -rf var/build/x86_64/tmp
