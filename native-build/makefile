#
# This makefile drives the native build done on a non-native system, i.e.,
# before building the native compiler, a cross compiler will be build.
# We then build the native compiler using the freshly-built cross
# compiler.
#
# The user running this script must have write access to /gcc
#
# Define CROSS_IS_PRESENT=1 if a suitable cross compiler is already
# present, in which case the cross compiler build is skipped, e.g.:
#
#  make CROSS_IS_PRESENT=1
#

ROOT_DIR=$(realpath .)

GMP_ARCHIVE=gmp-5.0.5.tar.bz2
MPFR_ARCHIVE=mpfr-3.1.2/mpfr-3.1.2.tar.bz2
MPC_ARCHIVE=mpc-0.9.tar.gz

BINUTILS_VERSION=2.23.2
BINUTILS_SRC_DIR=../binutils/repo

GCC_SRC_DIR=../gcc/repo
GCC_VERSION:=$(shell cat $(GCC_SRC_DIR)/gcc/BASE-VER)

# Native tools
COREUTILS_SRC_DIR=../coreutils/repo
COREUTILS_VERSION=5.2.1

CROSS_PREFIX?=$(ROOT_DIR)/root-cross
# This assumes that cross prefix is absolute
DESTDIR?=/

all: gcc-native-done-$(GCC_VERSION)

#
# Downloads the SDK and libraries necesseary to build the cross compiler
#
downloads-done:
	mkdir -p downloads
	wget "http://www.hyperion-entertainment.biz/index.php?option=com_registration&amp;view=download&amp;format=raw&amp;file=69&amp;Itemid=63" -O downloads/SDK_53.24.lha
	cd downloads && wget -N https://gmplib.org/download/gmp/$(GMP_ARCHIVE)
	cd downloads && wget -N http://www.mpfr.org/$(MPFR_ARCHIVE)
	cd downloads && wget -N http://www.multiprecision.org/mpc/download/$(MPC_ARCHIVE)
	touch $@

#
# Builds the cross binutils package (assembler, etc).
#
binutils-cross-build-done-$(BINUTILS_VERSION):
	$(MAKE) -C ../binutils-build SRC_DIR=$(BINUTILS_SRC_DIR) PREFIX=$(CROSS_PREFIX) CROSS_BUILD_DIR=$(ROOT_DIR)/binutils-cross-build-$(BINUTILS_VERSION)
	touch $@

.PHONY: binutils-build
binutils-build: binutils-cross-build-done-$(BINUTILS_VERSION)

#
# Installs the cross binutils package (assembler, etc).
#
binutils-cross-done-$(BINUTILS_VERSION): binutils-cross-build-done-$(BINUTILS_VERSION)
	$(MAKE) -C $(ROOT_DIR)/binutils-cross-build-$(BINUTILS_VERSION) install DESTDIR=$(DESTDIR)
	touch $@

.PHONY: binutils-install
binutils-install: binutils-cross-done-$(BINUTILS_VERSION)

#
# Prepares the includes
#
includes-done: downloads-done
	mkdir -p $(CROSS_PREFIX)/ppc-amigaos/SDK/include
	cd downloads && lha x SDK_53.24.lha
	cd downloads/SDK_Install && lha xf clib2*.lha
	cd downloads/SDK_Install && lha xf newlib*.lha
	cd downloads/SDK_Install && lha xf base.lha
	cd downloads/SDK_Install && rm -Rf *.lha
	cd downloads/SDK_Install && mv clib2* newlib* $(CROSS_PREFIX)/ppc-amigaos/SDK
	cd downloads/SDK_Install && mv Include/* $(CROSS_PREFIX)/ppc-amigaos/SDK/include
	rm -Rf downloads/SDK_Install downloads/SDK_Install.info
	touch $@

#
# Build the cross compiler
#
gcc-cross-done-$(GCC_VERSION): includes-done binutils-cross-done-$(BINUTILS_VERSION)
	$(MAKE) -C ../gcc-build SRC_DIR=$(GCC_SRC_DIR) PREFIX=$(CROSS_PREFIX) CROSS_BUILD_DIR=$(ROOT_DIR)/gcc-cross-build-$(GCC_VERSION) VERSION=$(GCC_VERSION)
	$(MAKE) -C $(ROOT_DIR)/gcc-cross-build-$(GCC_VERSION) install
	touch $@

.PHONY: gcc-cross
gcc-cross: gcc-cross-done-$(GCC_VERSION)

#
# Optional target for additional libs
#
.PHONY: additionals-libs
additionals-libs:
	mkdir -p $(CROSS_PREFIX)/ppc-amigaos/SDK/local/common/include
	mkdir -p /tmp/abcd
	cd downloads && lha xw=/tmp/abcd SDK_53.24.lha
	cd /tmp/abcd/SDK_Install && lha x pthread.lha && lha x zlib-1.2.3.lha
	cp -Rf /tmp/abcd/SDK_Install/Local/* $(CROSS_PREFIX)/ppc-amigaos/SDK/local
	rm -Rf /tmp/abcd


ifeq ($(CROSS_IS_PRESENT),1)
NATIVE_LIBRARY_DEPENDENCIES=
else
NATIVE_LIBRARY_DEPENDENCIES=gcc-cross-done-$(GCC_VERSION)
endif

#
# Build and install the libraries
#
libraries-done: $(NATIVE_LIBRARY_DEPENDENCIES)
	cd downloads && tar -xjf $(notdir $(GMP_ARCHIVE))
	cd downloads && tar -xjf $(notdir $(MPFR_ARCHIVE))
	cd downloads && tar -xzf $(notdir $(MPC_ARCHIVE))
	cd $(basename $(basename downloads/$(notdir $(GMP_ARCHIVE)))) && PATH="$(CROSS_PREFIX)/bin:$(PATH)" ./configure --host=ppc-amigaos --prefix=$(CROSS_PREFIX) && PATH="$(CROSS_PREFIX)/bin:$(PATH)" make install
	cd $(basename $(basename downloads/$(notdir $(MPFR_ARCHIVE)))) && PATH="$(CROSS_PREFIX)/bin:$(PATH)" ./configure --host=ppc-amigaos --prefix=$(CROSS_PREFIX) -with-gmp=$(CROSS_PREFIX) && PATH="$(CROSS_PREFIX)/bin:$(PATH)" make install
	cd $(basename $(basename downloads/$(notdir $(MPC_ARCHIVE)))) && PATH="$(CROSS_PREFIX)/bin:$(PATH)" ./configure --host=ppc-amigaos --prefix=$(CROSS_PREFIX) --with-gmp=$(CROSS_PREFIX) --with-mpfr=$(CROSS_PREFIX) && PATH="$(CROSS_PREFIX)/bin:$(PATH)" make install
	touch $@

#
# Build the native binutils
#
binutils-native-done-$(BINUTILS_VERSION): libraries-done
	PATH="$(CROSS_PREFIX)/bin:$(PATH)" $(MAKE) -C ../binutils-build native \
			SRC_DIR=$(BINUTILS_SRC_DIR) \
			PREFIX=/gcc \
			NATIVE_BUILD_DIR=$(ROOT_DIR)/binutils-native-build-$(BINUTILS_VERSION)
	touch $@

#
# Build the native gcc
#
gcc-native-done-$(GCC_VERSION): binutils-native-done-$(BINUTILS_VERSION)
	mkdir -p $(ROOT_DIR)/root-native/gcc/include
	mkdir -p /gcc/include
	PATH="$(CROSS_PREFIX)/bin:$(PATH)" $(MAKE) -C ../gcc-build native \
			SRC_DIR=$(GCC_SRC_DIR) \
			PREFIX=/gcc \
			NATIVE_BUILD_DIR=$(ROOT_DIR)/gcc-native-build-$(GCC_VERSION) \
			VERSION=$(GCC_VERSION) \
			LIB_PATH=$(CROSS_PREFIX) \
			NATIVE_SYS_ROOT=$(ROOT_DIR)/root-native
	touch $@

coreutils-native-done: gcc-cross-done-$(GCC_VERSION)
	mkdir -p coreutils-native-build
	cd coreutils-native-build ; PATH="$(CROSS_PREFIX)/bin:$(PATH)" LDFLAGS="-lunix" $(realpath $(COREUTILS_SRC_DIR))/configure --prefix=/gcc --host=ppc-amigaos
	PATH="$(CROSS_PREFIX)/bin:$(PATH)" $(MAKE) -C coreutils-native-build
	touch $@

#
# Install native compiler into /gcc. Needs write access to this directory
#
native-install: coreutils-native-done gcc-native-done-$(GCC_VERSION)
	rm -Rf /gcc/*
	PATH="$(CROSS_PREFIX)/bin:$(PATH)" $(MAKE) -C binutils-native-build-$(BINUTILS_VERSION) install
	PATH="$(CROSS_PREFIX)/bin:$(PATH)" $(MAKE) -C gcc-native-build-$(GCC_VERSION) install
	PATH="$(CROSS_PREFIX)/bin:$(PATH)" $(MAKE) -C coreutils-native-build install
	cp -R $(CROSS_PREFIX)/ppc-amigaos/SDK /gcc
	cp -Rf $(CROSS_PREFIX)/lib/gcc/ppc-amigaos /gcc/lib/gcc/
	# Move lib archives (e.g., libgcc.a into the proper directory)
	cd /gcc/lib/gcc ; for lib in `find -name *.a -o -name *.so`; do mkdir -p `dirname $$lib`/lib; mv $$lib `dirname $$lib`/lib ; done

#
# Strip native files
#
native-strip:
	$(MAKE) native-strip-really

native-strip-really:
	$(foreach var,$(wildcard /gcc/bin/*), $(CROSS_PREFIX)/bin/ppc-amigaos-strip --strip-all --strip-unneeded-rel-relocs $(var) ; ) true
	$(CROSS_PREFIX)/bin/ppc-amigaos-strip --strip-all --strip-unneeded-rel-relocs /gcc/libexec/gcc/ppc-amigaos/$(GCC_VERSION)/cc1
	$(CROSS_PREFIX)/bin/ppc-amigaos-strip --strip-all --strip-unneeded-rel-relocs /gcc/libexec/gcc/ppc-amigaos/$(GCC_VERSION)/cc1plus
	$(CROSS_PREFIX)/bin/ppc-amigaos-strip --strip-all --strip-unneeded-rel-relocs /gcc/libexec/gcc/ppc-amigaos/$(GCC_VERSION)/lto1
	$(CROSS_PREFIX)/bin/ppc-amigaos-strip --strip-all --strip-unneeded-rel-relocs /gcc/libexec/gcc/ppc-amigaos/$(GCC_VERSION)/lto-wrapper

native-dist: native-strip-really
	cd / && lha ao5 $(realpath .)/adtools-native-$(shell date +%Y%d%m)-$(shell git rev-list --count HEAD).lha gcc/*

#
# Cleanup everything
#
.PHONY: clean
clean:
	rm -Rf binutils-cross-build-$(BINUTILS_VERSION) binutils-native-build $(CROSS_PREFIX) build-cross-done binutils-cross-build-done-$(BINUTILS_VERSION) binutils-cross-done-$(BINUTILS_VERSION) binutils-native-done gcc-cross-build-$(GCC_VERSION) gcc-cross-done-$(GCC_VERSION) gcc-native-build-$(GCC_VERSION) gcc-native-done-$(GCC_VERSION) includes-done libraries-done root-native coreutils-native-build coreutils-native-done

#
# Cleanup really everything
#
.PNONY: clean-all
clean-all: clean
	rm -Rf downloads-done downloads
