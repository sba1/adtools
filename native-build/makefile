#
# This makefile drives the native build done on a non-native system, i.e.,
# before building the native compiler, a cross compiler will be build.
# We then build the native compiler using the freshly-built cross
# compiler.
#
# The user running this script must have write access to /gcc
#
# ===
CROSS_IS_PRESENT?=0
# Optional (DEFAULT=0):
# Define CROSS_IS_PRESENT=1 if a suitable cross compiler is already
# present, in which case the cross compiler build is skipped, e.g.:
#
#  make CROSS_IS_PRESENT=1
#
# ===
CLIB2_SHA1?=1a42c693e03881f6f969c43ab36ce20d2569751d
# Optional (DEFAULT 1a42c693e03881f6f969c43ab36ce20d2569751d)
# Define CLIB2_SHA1 to be the value of the branch or commit to use for clib2
# ===
CLIB4_SHA1?=HEAD
# Optional (DEFAULT HEAD)
# Define CLIB4_SHA1 to be the value of the branch or commit to use for clib4
#
# Note that CLIB4 is only supported for certain version of GCC, see
# the variable named "CLIB4_SUPPORT" below
# ===
SDK_VERSION?=54.16
# Optional (DEFAULT=54.16):
# Define SDK_VERSION to specify which version of the Amiga SDK is desired

ROOT_DIR=$(realpath .)

# Compiler setup, utilize ccache if available
CCACHE:=$(shell which ccache)
HOST_GCC:=$(strip $(CCACHE) gcc)
HOST_GXX:=$(strip $(CCACHE) g++)

GMP_ARCHIVE=gmp-5.1.3.tar.bz2
MPFR_ARCHIVE=mpfr-3.1.6.tar.bz2
MPC_ARCHIVE=mpc-1.0.3.tar.gz

BINUTILS_VERSION=2.23.2
BINUTILS_SRC_DIR=../binutils/repo

GCC_SRC_DIR=../gcc/repo
GCC_VERSION:=$(shell cat $(GCC_SRC_DIR)/gcc/BASE-VER)
GCC_DEV_PHASE:=$(shell cat ${GCC_SRC_DIR}/gcc/DEV-PHASE)

ifneq ($(GCC_DEV_PHASE),)
GCC_DEV_PHASE:= ($(GCC_DEV_PHASE))
endif

GCC_BRANCH_NAME:=$(word 1, $(subst ., , $(GCC_VERSION)))

# Handle SDK version and mapping to necessary file URL
ifeq (54.16,$(SDK_VERSION))
SDK_URL_FILE=127
else
ifeq (53.34,$(SDK_VERSION))
SDK_URL_FILE=125
else
ifeq (53.30,$(SDK_VERSION))
SDK_URL_FILE=82
else
ifeq (53.24,$(SDK_VERSION))
SDK_URL_FILE=69
else
ifneq (54.16,$(SDK_VERSION))
$(error Unexpected SDK_VERSION supplied)
endif
endif
endif
endif
endif
SDK_URL=http://www.hyperion-entertainment.biz/index.php?option=com_registration&amp;view=download&amp;format=raw&amp;file=$(SDK_URL_FILE)

# Native tools
COREUTILS_SRC_DIR=../coreutils/repo
COREUTILS_VERSION=5.2.1

# Distribution version, used as middle part of a distribution archive
DIST_VERSION=$(shell date +%Y%m%d)-$(shell git rev-list --count HEAD)

# Set up the necessary variables for the CLIBs
CLIB4_SUPPORT=$(filter 11 8 6,$(GCC_BRANCH_NAME))
CLIB4_URL=https://github.com/AmigaLabs/clib4
CLIB4_DIR=downloads/clib4/
CLIB4_RELEASE_ARCHIVE_NAME=adtools-os4-clib4-$(DIST_VERSION).lha

CLIB2_URL=https://github.com/sodero/clib2
CLIB2_DIR=downloads/clib2/library/
CLIB2_RELEASE_ARCHIVE_NAME=adtools-os4-clib2-$(DIST_VERSION).lha

CROSS_PREFIX?=$(ROOT_DIR)/root-cross
# This assumes that cross prefix is absolute
DESTDIR?=

STRIP=$(CROSS_PREFIX)/bin/ppc-amigaos-strip
STRIPFLAGS=--strip-all --strip-unneeded-rel-relocs -R.comment

all: gcc-native-done-$(GCC_VERSION)

#
# Print the dist version that is used as suffix for various
# suffixes.
#
.PHONY: print-dist-version
print-dist-version:
	@echo $(DIST_VERSION)

#
# Downloads clib2
#
downloads-done-clib2:
	mkdir -p downloads
	cd downloads && \
		(git clone $(CLIB2_URL) clib2 || true) && \
		cd clib2 && \
		git checkout $(CLIB2_SHA1)
	touch $@

#
# Downloads clib4
#
ifneq ($(CLIB4_SUPPORT),)
downloads-done-clib4:
	mkdir -p downloads
	cd downloads && \
		(git clone $(CLIB4_URL) clib4 || true) && \
		cd clib4 && \
		git checkout $(CLIB4_SHA1)
	touch $@
endif

#
# Downloads the SDK and libraries necesseary to build the cross compiler
#
DOWNLOADS_DONE_DEPENDENCY=downloads-done-clib2
ifneq ($(CLIB4_SUPPORT),)
DOWNLOADS_DONE_DEPENDENCY+=downloads-done-clib4
endif
downloads-done: $(DOWNLOADS_DONE_DEPENDENCY)
	wget "$(SDK_URL)" -O downloads/SDK_$(SDK_VERSION).lha
	cd downloads && wget -N http://ftp.gnu.org/gnu/gmp/$(GMP_ARCHIVE)
	cd downloads && wget -N http://ftp.gnu.org/gnu/mpfr/$(MPFR_ARCHIVE)
	cd downloads && wget -N http://ftp.gnu.org/gnu/mpc/$(MPC_ARCHIVE)
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
	cd downloads && lha x SDK_$(SDK_VERSION).lha
	cd downloads/SDK_Install && lha xf newlib*.lha
	cd downloads/SDK_Install && lha xf base.lha
ifneq (53.30,$(SDK_VERSION))
ifneq (53.24,$(SDK_VERSION))
	cd downloads/SDK_Install && lha xf execsg*.lha
endif
endif
	cd downloads/SDK_Install && rm -Rf *.lha
	cd downloads/SDK_Install && mv newlib* $(CROSS_PREFIX)/ppc-amigaos/SDK
	cd downloads/SDK_Install && mv Include/* $(CROSS_PREFIX)/ppc-amigaos/SDK/include
	rm -Rf downloads/SDK_Install downloads/SDK_Install.info
	touch $@

#
# Path to the initial cross compiler or standard
# cross compiler if a cross compiler is present
#

ifeq ($(CROSS_IS_PRESENT),1)

XGCC=ppc-amigaos-gcc
XGCC_CC=ppc-amigaos-gcc
XAR=ppc-amigaos-ar -q
XRANLIB=ppc-amigaos-ranlib

CLIB_CROSS_DONE_DEPENDENCY=downloads-done-clib2
ifneq ($(CLIB4_SUPPORT),)
CLIB_CROSS_DONE_DEPENDENCY+=downloads-done-clib4
endif

else

XGCC_DIR=$(abspath .)/gcc-cross-build-$(GCC_VERSION)/gcc
XGCC=$(XGCC_DIR)/xgcc
XGCC_CC=$(XGCC) -B $(XGCC_DIR)
XAR=$(CROSS_PREFIX)/bin/ppc-amigaos-ar -q
XRANLIB=$(CROSS_PREFIX)/bin/ppc-amigaos-ranlib

CLIB_CROSS_DONE_DEPENDENCY=xgcc-done-$(GCC_VERSION)

endif

#
# Prints the folder where the basic xg (xgcc or xg++) compilers
# can be round.
#
.PHONY: print-xg-dir
print-xg-dir:
	@echo $(XGCC_DIR)

#
# Build only xgcc, no other stuff like libstdc++ etc.
#
xgcc-done-$(GCC_VERSION): includes-done binutils-cross-done-$(BINUTILS_VERSION)
	CC="$(HOST_GCC)" CXX="$(HOST_GXX)" $(MAKE) -C ../gcc-build cross-configure \
		SRC_DIR=$(GCC_SRC_DIR) \
		PREFIX=$(CROSS_PREFIX) \
		CROSS_BUILD_DIR=$(ROOT_DIR)/gcc-cross-build-$(GCC_VERSION) \
		VERSION=$(GCC_VERSION)
	$(MAKE) -C $(ROOT_DIR)/gcc-cross-build-$(GCC_VERSION) all-gcc
	touch $@

#
# Build clib via xgcc
#
ifneq ($(CLIB4_SUPPORT),)
clib4-cross-done-$(GCC_VERSION): $(CLIB_CROSS_DONE_DEPENDENCY)
# Build clib using xgcc that have just been built
	$(MAKE) -C $(CLIB4_DIR) -f GNUmakefile.os4 \
		CC="$(XGCC_CC)" \
		AR="$(XAR)" \
		RANLIB="$(XRANLIB)" \
		STRIP=$(STRIP) \
		INSTALL_PREFIX=$(CROSS_PREFIX)/ppc-amigaos/SDK/clib4 \
		SDK_INCLUDE=$(CROSS_PREFIX)/ppc-amigaos/SDK/include
# Copy clib libs and includes
	$(MAKE) -C $(CLIB4_DIR) -f GNUmakefile.os4 install \
		INSTALL_PREFIX=$(CROSS_PREFIX)/ppc-amigaos/SDK/clib4
	cp $(CLIB4_DIR)/LICENSE* $(CROSS_PREFIX)/ppc-amigaos/SDK/clib4
	touch $@
endif

clib2-cross-done-$(GCC_VERSION): $(CLIB_CROSS_DONE_DEPENDENCY)
# Build clib using xgcc that have just been built
	$(MAKE) -C $(CLIB2_DIR) -f GNUmakefile.os4 \
		CC="$(XGCC_CC)" \
		AR="$(XAR)" \
		RANLIB="$(XRANLIB)"
# Copy clib libs and includes
	rm -Rf $(CROSS_PREFIX)/ppc-amigaos/SDK/clib2/lib $(CROSS_PREFIX)/ppc-amigaos/SDK/clib2/include
	mkdir -p $(CROSS_PREFIX)/ppc-amigaos/SDK/clib2/lib
	mkdir -p $(CROSS_PREFIX)/ppc-amigaos/SDK/clib2/include
	cp -Rp $(CLIB2_DIR)/include/* $(CROSS_PREFIX)/ppc-amigaos/SDK/clib2/include
	cp -Rp $(CLIB2_DIR)/lib/* $(CROSS_PREFIX)/ppc-amigaos/SDK/clib2/lib
	cp $(CLIB2_DIR)/../LICENSE $(CROSS_PREFIX)/ppc-amigaos/SDK/clib2
	touch $@

#
# Build the cross compiler
#
GCC_CROSS_DONE_DEPENDENCY=clib2-cross-done-$(GCC_VERSION)
ifneq ($(CLIB4_SUPPORT),)
GCC_CROSS_DONE_DEPENDENCY+=clib4-cross-done-$(GCC_VERSION)
endif
gcc-cross-done-$(GCC_VERSION): $(GCC_CROSS_DONE_DEPENDENCY)
# Compile remaining
	$(MAKE) -C $(ROOT_DIR)/gcc-cross-build-$(GCC_VERSION)
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
	cd downloads && lha xw=/tmp/abcd SDK_$(SDK_VERSION).lha
	cd /tmp/abcd/SDK_Install && lha x pthread.lha && lha x zlib-1.2.3.lha
	cp -Rf /tmp/abcd/SDK_Install/Local/* $(CROSS_PREFIX)/ppc-amigaos/SDK/local
	rm -Rf /tmp/abcd


ifeq ($(CROSS_IS_PRESENT),1)
NATIVE_LIBRARY_DEPENDENCIES=downloads-done
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

ifeq ($(CROSS_IS_PRESENT),1)
coreutils-native-done:
else

coreutils-native-done: gcc-cross-done-$(GCC_VERSION)
endif
	mkdir -p coreutils-native-build
	@if [ ! -f $(COREUTILS_SRC_DIR)/configure ]; then echo "Please checkout coreutils first!"; false; fi
# Pretend few files to be uptodate
	touch $(realpath $(COREUTILS_SRC_DIR))/configure $(realpath $(COREUTILS_SRC_DIR))/config.hin
	cd coreutils-native-build ; \
		$(realpath $(COREUTILS_SRC_DIR))/configure --prefix=/gcc --host=ppc-amigaos --disable-maintainer-mode \
		PATH="$(CROSS_PREFIX)/bin:$(PATH)" \
		CPPFLAGS="-mcrt=clib2" \
		LDFLAGS="-mcrt=clib2" \
		LIBS="-lunix -lnet"
	PATH="$(CROSS_PREFIX)/bin:$(PATH)" $(MAKE) -C coreutils-native-build
	touch $@


GCC_BASE_BRANCH_NAME=$(GCC_BRANCH_NAME)-base
#
# Build the main docs
#
.PHONY: doc
doc:
	rm -Rf $@
	mkdir -p $@/tmp/orig
	mkdir -p $@/tmp/patched

	echo "@set version-GCC $(GCC_VERSION)-adtools" >$@/tmp/orig/gcc-vers.texi
	echo "@set srcdir $(ROOT_DIR)/$(GCC_BASE_BRANCH_NAME)/gcc" >>$@/tmp/orig/gcc-vers.texi
	echo "@set BUGURL https://github.com/sba1/adtools/issues" >>$@/tmp/orig/gcc-vers.texi

	echo "@set version-GCC $(GCC_VERSION)-adtools" >$@/tmp/patched/gcc-vers.texi
	echo "@set srcdir $(GCC_SRC_DIR)/gcc" >>$@/tmp/patched/gcc-vers.texi
	echo "@set BUGURL https://github.com/sba1/adtools/issues" >>$@/tmp/patched/gcc-vers.texi

	# Checkout base branch as worktree
	cd $(GCC_SRC_DIR) && git worktree add -f $(ROOT_DIR)/$(GCC_BASE_BRANCH_NAME) $(GCC_BASE_BRANCH_NAME) || true
	cd $(ROOT_DIR)/$(GCC_BASE_BRANCH_NAME) && git checkout --detach $(GCC_BASE_BRANCH_NAME)

	makeinfo --plaintext -I $(GCC_BASE_BRANCH_NAME)/gcc/doc -I $(GCC_BASE_BRANCH_NAME)/gcc/doc/include -I $@/tmp/orig -o $@/tmp/orig/gcc.txt $(GCC_BASE_BRANCH_NAME)/gcc/doc/gcc.texi
	makeinfo --plaintext -I $(GCC_BASE_BRANCH_NAME)/gcc/doc -I $(GCC_BASE_BRANCH_NAME)/gcc/doc/include -I $@/tmp/orig -o $@/tmp/orig/cpp.txt $(GCC_BASE_BRANCH_NAME)/gcc/doc/cpp.texi

	makeinfo --plaintext -I $(GCC_SRC_DIR)/gcc/doc -I $(GCC_SRC_DIR)/gcc/doc/include -I $@/tmp/patched -o $@/tmp/patched/gcc.txt $(GCC_SRC_DIR)/gcc/doc/gcc.texi
	makeinfo --plaintext -I $(GCC_SRC_DIR)/gcc/doc -I $(GCC_SRC_DIR)/gcc/doc/include -I $@/tmp/patched -o $@/tmp/patched/cpp.txt $(GCC_SRC_DIR)/gcc/doc/cpp.texi

	cd $@/tmp && bash -c "wdiff -n -w $$'\033[30;41m' -x $$'\033[0m' -y $$'\033[30;42m' -z $$'\033[0m' orig/gcc.txt patched/gcc.txt >../gcc.txt" || true
	cd $@/tmp && bash -c "wdiff -n -w $$'\033[30;41m' -x $$'\033[0m' -y $$'\033[30;42m' -z $$'\033[0m' orig/cpp.txt patched/cpp.txt >../cpp.txt" || true

	rm -Rf $@/tmp
#
# Target for generating the ReadMe used for Aminet
#
ifneq ($(CLIB4_SUPPORT),)
CLIB4_ENTRY=CLIB4_RELEASE_ARCHIVE_NAME='$(CLIB4_RELEASE_ARCHIVE_NAME)'
else
CLIB4_ENTRY=CLIB4_RELEASE_ARCHIVE_NAME='<NOT GENERATED>'
endif
ReadMe: ReadMe.mak
	python -c "\
	from mako.template import Template;\
	from mako.lookup import TemplateLookup;\
	print (Template(\
		filename='$<',\
		input_encoding='utf-8',\
		output_encoding='utf-8',\
		lookup=TemplateLookup(['./'],input_encoding='utf-8')).render(\
			DIST_VERSION='$(DIST_VERSION)',\
			ADTOOLS_COMMIT_SHA1='$(shell git rev-list HEAD -1)',\
			BINUTILS_VERSION='$(BINUTILS_VERSION)',\
			GCC_VERSION='$(GCC_VERSION)',\
			GCC_DEV_PHASE='$(GCC_DEV_PHASE)',\
			COREUTILS_VERSION='$(COREUTILS_VERSION)',\
			CLIB2_RELEASE_ARCHIVE_NAME='$(CLIB2_RELEASE_ARCHIVE_NAME)',\
			$(CLIB4_ENTRY)\
		))\
	" >$@.utf8
	iconv --from-code=UTF8 --to-code=ISO-8859-15 $@.utf8 >$@

# Function to make a file whose name is prefixed by the target alias
# but which is the same as the given one.
#
# We use cp here until we know that softlinks would work properly.
define MAKE_TARGET_ALIAS
	cp /gcc/bin/$(1) /gcc/bin/ppc-amigaos-$(1)
endef

# A simple macro for inserting a newline
define NL


endef

#
# Lists all executable files that are produced by the binutils steps
# and that also should be reachable via a target alias prefix.
#
BINUTILS_EXES = \
	addr2line \
	ar \
	as \
	c++filt \
	elfedit \
	gprof \
	ld \
	ld.bfd \
	nm \
	objcopy \
	objdump \
	ranlib \
	readelf \
	size \
	strings \
	strip

#
# Install native compiler into /gcc. Needs write access to this directory
#
native-install: coreutils-native-done gcc-native-done-$(GCC_VERSION) ReadMe doc
	rm -Rf /gcc/*
	PATH="$(CROSS_PREFIX)/bin:$(PATH)" $(MAKE) -C binutils-native-build-$(BINUTILS_VERSION) install
# Create copies of few files that usually are also accessible via a filename with the target alias prefix
	$(foreach EXE, $(BINUTILS_EXES), $(call MAKE_TARGET_ALIAS,$(EXE))$(NL))
	PATH="$(CROSS_PREFIX)/bin:$(PATH)" $(MAKE) -C gcc-native-build-$(GCC_VERSION) install
	PATH="$(CROSS_PREFIX)/bin:$(PATH)" $(MAKE) -C coreutils-native-build install
# Disabled SDK as we don't want to distribute it
#	cp -R $(CROSS_PREFIX)/ppc-amigaos/SDK /gcc
# Disabled, because we don't want to copy from CROSS_PREFIX here
#	cp -Rf $(CROSS_PREFIX)/lib/gcc/ppc-amigaos /gcc/lib/gcc/
	# Delete all but our target gcc libs
	find /gcc/lib/gcc/ppc-amigaos -mindepth 1 -maxdepth 1 -not -name $(GCC_VERSION) | xargs rm -Rf
# Disabled, no longer required
#	# Move lib archives (e.g., libgcc.a into the proper directory)
#	cd /gcc/lib/gcc ; for lib in `find -name *.a -o -name *.so`; do mkdir -p `dirname $$lib`/lib; mv $$lib `dirname $$lib`/lib ; done
	cp ReadMe /gcc
	mkdir -p /gcc/doc
	cp doc/* /gcc/doc

#
# Similar to native-install but deploys the components in separate directories
#
native-separate-install:
	rm -Rf root-native-binutils
	rm -Rf root-native-gcc
	rm -Rf root-native-coreutils
	PATH="$(CROSS_PREFIX)/bin:$(PATH)" $(MAKE) -C binutils-native-build-$(BINUTILS_VERSION) install DESTDIR=$(ROOT_DIR)/root-native-binutils
	PATH="$(CROSS_PREFIX)/bin:$(PATH)" $(MAKE) -C gcc-native-build-$(GCC_VERSION) install DESTDIR=$(ROOT_DIR)/root-native-gcc
	PATH="$(CROSS_PREFIX)/bin:$(PATH)" $(MAKE) -C coreutils-native-build install DESTDIR=$(ROOT_DIR)/root-native-coreutils
	$(MAKE) private-native-separate-dist

# Private target. Unfinished
private-native-separate-dist:
	$(foreach var,$(wildcard $(ROOT_DIR)/root-native-coreutils/gcc/bin/*), $(STRIP) $(STRIPFLAGS) $(var) ; ) true
	$(foreach var,$(wildcard $(ROOT_DIR)/root-native-binutils/gcc/bin/*), $(STRIP) $(STRIPFLAGS) $(var) ; ) true
	$(foreach var,$(wildcard $(ROOT_DIR)/root-native-gcc/gcc/bin/*), $(STRIP) $(STRIPFLAGS) $(var) ; ) true
	$(STRIP) $(STRIPFLAGS) $(ROOT_DIR)/root-native-gcc/gcc/libexec/gcc/ppc-amigaos/$(GCC_VERSION)/cc1
	$(STRIP) $(STRIPFLAGS) $(ROOT_DIR)/root-native-gcc/gcc/libexec/gcc/ppc-amigaos/$(GCC_VERSION)/cc1plus
	$(STRIP) $(STRIPFLAGS) $(ROOT_DIR)/root-native-gcc/gcc/libexec/gcc/ppc-amigaos/$(GCC_VERSION)/lto1
	$(STRIP) $(STRIPFLAGS) $(ROOT_DIR)/root-native-gcc/gcc/libexec/gcc/ppc-amigaos/$(GCC_VERSION)/lto-wrapper
	rm -Rf dist
	mkdir -p dist/coreutils-$(COREUTILS_VERSION)-$(DIST_VERSION)

#
# Strip native files
#
native-strip:
# Invoke make recursively with another target so that $(wildcard) is properly resolved.
	$(MAKE) native-strip-really

native-strip-really:
	$(foreach var,$(wildcard /gcc/bin/*), $(STRIP) --strip-all --strip-unneeded-rel-relocs $(var) ; ) true
	$(STRIP) $(STRIPFLAGS) /gcc/libexec/gcc/ppc-amigaos/$(GCC_VERSION)/cc1
	$(STRIP) $(STRIPFLAGS) /gcc/libexec/gcc/ppc-amigaos/$(GCC_VERSION)/cc1plus
	$(STRIP) $(STRIPFLAGS) /gcc/libexec/gcc/ppc-amigaos/$(GCC_VERSION)/lto1
	$(STRIP) $(STRIPFLAGS) /gcc/libexec/gcc/ppc-amigaos/$(GCC_VERSION)/lto-wrapper

#
# Native distribution archive
#
DIST_FOLDER:=adtools-os4-$(GCC_BRANCH_NAME)-$(DIST_VERSION)

native-dist: native-strip-really
	rm -f $(realpath .)/$(DIST_FOLDER).lha
	rm -Rf /tmp/$(DIST_FOLDER)
	mkdir /tmp/$(DIST_FOLDER)
	cp -pR /gcc/* /tmp/$(DIST_FOLDER)

	# Deduplicate
	../bin/dedup /tmp/$(DIST_FOLDER) >.dedup
	echo "; Create alternative filenames" >/tmp/$(DIST_FOLDER)/RestoreLinks
	../bin/dedup /tmp/$(DIST_FOLDER) --amigaos --folder-is-pwd >>/tmp/$(DIST_FOLDER)/RestoreLinks
# Disbaled until we find a way to keep softlinks via lha
#	sh -x .dedup
#	rm .dedup

	cd /tmp && lha ao5 $(realpath .)/$(DIST_FOLDER).lha $(DIST_FOLDER)/*

#
# Clib distribution
#
clib2-dist: clib2-cross-done-$(GCC_VERSION)
	cd root-cross/ppc-amigaos/SDK && lha ao5 $(realpath .)/$(CLIB2_RELEASE_ARCHIVE_NAME) clib2
ifneq ($(CLIB4_SUPPORT),)
clib4-dist: clib4-cross-done-$(GCC_VERSION)
	cd root-cross/ppc-amigaos/SDK && lha ao5 $(realpath .)/$(CLIB4_RELEASE_ARCHIVE_NAME) clib4
endif

#
# Upload the binary archive to the main Aminet server
#
.PHONY: upload-release
upload-release: native-dist
	ln -s $(DIST_FOLDER).lha adtools-$(GCC_BRANCH_NAME)-os4.lha
	lftp -e "put adtools-$(GCC_BRANCH_NAME)-os4.lha && put ReadMe -o adtools-$(GCC_BRANCH_NAME)-os4.readme && quit" ftp://main.aminet.net/new

#
# Cleanup clib
#

.PHONY: clean-clib2
clean-clib2:
	test ! -d $(CLIB2_DIR) || $(MAKE) -C $(CLIB2_DIR) -f GNUmakefile.os4 clean
clean-clib4:
	test ! -d $(CLIB4_DIR) || $(MAKE) -C $(CLIB4_DIR) -f GNUmakefile.os4 clean

#
# Cleanup gcc only
#

.PHONY: clean-gcc
clean-gcc:
	rm -Rf \
		xgcc-done-$(GCC_VERSION) \
		gcc-cross-build-$(GCC_VERSION) \
		gcc-cross-done-$(GCC_VERSION) \
		gcc-native-build-$(GCC_VERSION) \
		gcc-native-done-$(GCC_VERSION)

#
# Cleanup everything
#
.PHONY: clean
clean: clean-clib2 clean-clib4 clean-gcc
	rm -Rf	\
		binutils-cross-build-$(BINUTILS_VERSION) \
		binutils-native-build-$(BINUTILS_VERSION) \
		$(CROSS_PREFIX) \
		build-cross-done \
		binutils-cross-build-done-$(BINUTILS_VERSION) \
		binutils-cross-done-$(BINUTILS_VERSION) \
		binutils-native-done-$(BINUTILS_VERSION) \
		clib2-cross-done-$(GCC_VERSION) \
		clib4-cross-done-$(GCC_VERSION) \
		includes-done \
		libraries-done \
		root-native \
		coreutils-native-build \
		coreutils-native-done

#
# Cleanup really everything
#
.PNONY: clean-all
clean-all: clean
	rm -Rf downloads-done downloads-done-clib2 downloads-done-clib4 downloads
