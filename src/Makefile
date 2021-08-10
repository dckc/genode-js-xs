ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
BUILD_DIR=$(realpath $(ROOT_DIR)/../var/build/x86_64)
MODDABLE=$(realpath $(BUILD_DIR)/../../../vendor/moddable)
VERBOSE=1
# Use XS wasm platform, which has cross-compilation support.
CROSS_PLATFORM=genode
GOAL=debug

HOST_OS := $(shell uname)
ifeq ($(HOST_OS),Darwin)
MODDABLE_TOOLS_DIR = $(MODDABLE)/build/bin/mac
else
MODDABLE_TOOLS_DIR = $(MODDABLE)/build/bin/lin
endif

# avoid setting mxMacOSX=1 by default, which results in:
# xsString.c:42:11: fatal error: CoreServices/CoreServices.h: No such file or directory
#@@@ HINTS = -Dlinux=1

# `goa build` sets up all sorts of CPPFLAGS (-I...) and such; pass them to the xs makefile
# https://www.gnu.org/software/make/manual/html_node/Variables_002fRecursion.html#Variables_002fRecursion
export CPPFLAGS LIB_SRC CFLAGS LDFLAGS LDLIBS CXX CC VERBOSE GOAL BUILD_DIR MODDABLE

# target is $(BUILD_DIR)/bin/$(PLATFORM)/$(GOAL)/xst @@@
# but this Makefile doesn't know the dependencies,
# so always use the xs makefile.

# passing CPPFLAGS and such via `make CC=...` seems awkward
# but it was the only way I could get it to work.

# See also ../vendor/moddable-xst.patch
# for changes to LIBRARIES, LINK_OPTIONS

# XS binaries are named after the directory containing manifest.json
# TODO: make a subdir?
# See also manifest.json
NAME=hello

GEN_SRC=$(BUILD_DIR)/tmp/$(CROSS_PLATFORM)/$(GOAL)/$(NAME)

build: $(GEN_SRC)/makefile
	@echo BUILD_DIR=$(BUILD_DIR)
	@echo MODDABLE=$(MODDABLE)
	make -C $(GEN_SRC) \
		BUILD_DIR=$(BUILD_DIR) \
		MODDABLE=$(MODDABLE) \
		MODDABLE_TOOLS_DIR=$(MODDABLE_TOOLS_DIR) \
		CC="$(CC) $(CPPFLAGS) $(HINTS)"

gen_src: $(GEN_SRC)/makefile

$(GEN_SRC)/makefile:
	mcconfig -d -o $(BUILD_DIR) -p $(CROSS_PLATFORM)

what-env-might-help:
	env | grep genode-js-xs

clean:
	rm -rf $(ROOT_DIR)/../var/build/x86_64
