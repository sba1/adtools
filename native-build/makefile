#
# This makefile drives the native build done on a non-native system, i.e.,
# before building the native compiler, a cross compiler will be build.
# We then build the native compiler using the freshly-built cross
# compiler.
#
# The user running this script must have write access to /gcc
#

ROOT_DIR=$(realpath .)

GMP_ARCHIVE=gmp-5.0.5/gmp-5.0.5.tar.bz2
MPFR_ARCHIVE=mpfr-3.1.2/mpfr-3.1.2.tar.bz2
MPC_ARCHIVE=mpc-0.9.tar.gz

#BINUTILS_VERSION=2.23.2
#BINUTILS_SRC_DIR=../../branches/binutils/2.23.2
#BINUTILS_VERSION=2.19.1
#BINUTILS_SRC_DIR=../../branches/binutils/2.19.1
BINUTILS_VERSION=2.18
BINUTILS_SRC_DIR=../binutils

#GCC_VERSION=4.9.1
#GCC_SRC_DIR=../../branches/gcc/4.9.x/
GCC_VERSION=4.5.4
GCC_SRC_DIR=../../branches/gcc/4.5.x/

all: gcc-native-done-$(GCC_VERSION)

#
# Downloads the SDK and libraries necesseary to build the cross compiler
#
downloads-done:
	mkdir -p downloads
	wget "http://www.hyperion-entertainment.biz/index.php?option=com_registration&amp;view=download&amp;format=raw&amp;file=38&amp;Itemid=63" -O downloads/SDK_53.20.lha
	cd downloads && wget -N ftp://ftp.gmplib.org/pub/$(GMP_ARCHIVE)
	cd downloads && wget -N http://www.mpfr.org/$(MPFR_ARCHIVE)
	cd downloads && wget -N http://www.multiprecision.org/mpc/download/$(MPC_ARCHIVE)
	touch $@

#
# Builds the cross binutils package (assembler, etc).
#
binutils-cross-done-$(BINUTILS_VERSION):
	$(MAKE) -C ../binutils-build SRC_DIR=$(BINUTILS_SRC_DIR) PREFIX=$(ROOT_DIR)/root-cross CROSS_BUILD_DIR=$(ROOT_DIR)/binutils-cross-build-$(BINUTILS_VERSION)
	$(MAKE) -C $(ROOT_DIR)/binutils-cross-build-$(BINUTILS_VERSION) install
	touch $@

#
# Prepares the includes
#
includes-done: downloads-done
	mkdir -p $(ROOT_DIR)/root-cross/ppc-amigaos/SDK/include
	cd downloads && lha x SDK_53.20.lha
	cd downloads/SDK_Install && lha xf clib2*.lha
	cd downloads/SDK_Install && lha xf newlib*.lha
	cd downloads/SDK_Install && lha xf base.lha
	cd downloads/SDK_Install && rm -Rf *.lha
	cd downloads/SDK_Install && mv clib2* newlib* $(ROOT_DIR)/root-cross/ppc-amigaos/SDK
	cd downloads/SDK_Install && mv Include/* $(ROOT_DIR)/root-cross/ppc-amigaos/SDK/include
	rm -Rf downloads/SDK_Install downloads/SDK_Install.info
	touch $@

#
# Build the cross compiler
#
gcc-cross-done-$(GCC_VERSION): includes-done binutils-cross-done-$(BINUTILS_VERSION)
	$(MAKE) -C ../gcc-build SRC_DIR=$(GCC_SRC_DIR) PREFIX=$(ROOT_DIR)/root-cross CROSS_BUILD_DIR=$(ROOT_DIR)/gcc-cross-build-$(GCC_VERSION) VERSION=$(GCC_VERSION)
	$(MAKE) -C $(ROOT_DIR)/gcc-cross-build-$(GCC_VERSION) install
	touch $@

.PHONY: gcc-cross
gcc-cross: gcc-cross-done-$(GCC_VERSION)

#
# Optional target for additional libs
#
.PHONY: additionals-libs
additionals-libs:
	mkdir -p $(ROOT_DIR)/root-cross/ppc-amigaos/SDK/local/common/include
	mkdir -p /tmp/abcd
	cd downloads && lha xw=/tmp/abcd SDK_53.20.lha
	cd /tmp/abcd/SDK_Install && lha x pthread.lha && lha x zlib-1.2.3.lha
	cp -Rf /tmp/abcd/SDK_Install/Local/* $(ROOT_DIR)/root-cross/ppc-amigaos/SDK/local
	rm -Rf /tmp/abcd

#
# Build and install the libraries
#
libraries-done: gcc-cross-done-$(GCC_VERSION)
	cd downloads && tar -xjf $(notdir $(GMP_ARCHIVE))
	cd downloads && tar -xjf $(notdir $(MPFR_ARCHIVE))
	cd downloads && tar -xzf $(notdir $(MPC_ARCHIVE))
	cd $(basename $(basename downloads/$(notdir $(GMP_ARCHIVE)))) && PATH="$(ROOT_DIR)/root-cross/bin:$(PATH)" ./configure --host=ppc-amigaos --prefix=$(ROOT_DIR)/root-cross && PATH="$(ROOT_DIR)/root-cross/bin:$(PATH)" make install
	cd $(basename $(basename downloads/$(notdir $(MPFR_ARCHIVE)))) && PATH="$(ROOT_DIR)/root-cross/bin:$(PATH)" ./configure --host=ppc-amigaos --prefix=$(ROOT_DIR)/root-cross -with-gmp=$(ROOT_DIR)/root-cross && PATH="$(ROOT_DIR)/root-cross/bin:$(PATH)" make install
	cd $(basename $(basename downloads/$(notdir $(MPC_ARCHIVE)))) && PATH="$(ROOT_DIR)/root-cross/bin:$(PATH)" ./configure --host=ppc-amigaos --prefix=$(ROOT_DIR)/root-cross --with-gmp=$(ROOT_DIR)/root-cross --with-mpfr=$(ROOT_DIR)/root-cross && PATH="$(ROOT_DIR)/root-cross/bin:$(PATH)" make install
	touch $@

#
# Build the native binutils
#
binutils-native-done-$(BINUTILS_VERSION): libraries-done
	PATH="$(ROOT_DIR)/root-cross/bin:$(PATH)" $(MAKE) -C ../binutils-build native \
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
	PATH="$(ROOT_DIR)/root-cross/bin:$(PATH)" $(MAKE) -C ../gcc-build native \
			SRC_DIR=$(GCC_SRC_DIR) \
			PREFIX=/gcc \
			NATIVE_BUILD_DIR=$(ROOT_DIR)/gcc-native-build-$(GCC_VERSION) \
			VERSION=$(GCC_VERSION) \
			LIB_PATH=$(ROOT_DIR)/root-cross \
			NATIVE_SYS_ROOT=$(ROOT_DIR)/root-native
	touch $@

coreutils-native-done: gcc-cross-done-$(GCC_VERSION)
	mkdir -p coreutils-native-build
	cd coreutils-native-build ; PATH="$(ROOT_DIR)/root-cross/bin:$(PATH)" LDFLAGS="-lunix" ../../coreutils/configure --prefix=/gcc --host=ppc-amigaos
	PATH="$(ROOT_DIR)/root-cross/bin:$(PATH)" $(MAKE) -C coreutils-native-build
	touch $@

#
# Install native compiler into /gcc. Needs write acess to this directory
#
native-install: coreutils-native-done gcc-native-done-$(GCC_VERSION)
	rm -Rf /gcc/*
	PATH="$(ROOT_DIR)/root-cross/bin:$(PATH)" $(MAKE) -C binutils-native-build install
	PATH="$(ROOT_DIR)/root-cross/bin:$(PATH)" $(MAKE) -C gcc-native-build-$(GCC_VERSION) install
	PATH="$(ROOT_DIR)/root-cross/bin:$(PATH)" $(MAKE) -C coreutils-native-build install
	cp -R $(ROOT_DIR)/root-cross/ppc-amigaos/SDK /gcc
	cp -Rf $(ROOT_DIR)/root-cross/lib/gcc/ppc-amigaos /gcc/lib/gcc/
	# Move lib archives (e.g., libgcc.a into the proper directory)
	cd /gcc/lib/gcc ; for lib in `find -name *.a -o -name *.so`; do mkdir -p `dirname $$lib`/lib; mv $$lib `dirname $$lib`/lib ; done

#
# Cleanup everything
#
.PHONY: clean
clean:
	rm -Rf binutils-cross-build-$(BINUTILS_VERSION) binutils-native-build root-cross build-cross-done downloads-done downloads binutils-cross-done-$(BINUTILS_VERSION) binutils-native-done gcc-cross-build-$(GCC_VERSION) gcc-cross-done-$(GCC_VERSION) gcc-native-build-$(GCC_VERSION) gcc-native-done-$(GCC_VERSION) includes-done libraries-done root-native coreutils-native-build coreutils-native-done
