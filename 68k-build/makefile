ROOT_DIR=$(realpath .)

BINUTILS_VERSION=2.23.2
BINUTILS_SRC_DIR=../binutils/repo

GCC_SRC_DIR=../gcc/repo
GCC_VERSION:=$(shell cat $(GCC_SRC_DIR)/gcc/BASE-VER)

OUTPUT = $(ROOT_DIR)/output

all: binutils-cross-build-done-$(BINUTILS_VERSION) \
	gcc-cross-build-done-$(GCC_VERSION)

binutils-cross-build-done-$(BINUTILS_VERSION):
	mkdir -p $(OUTPUT)/$@
	cd $(OUTPUT)/$@ && CFLAGS="-Wno-switch -Wno-unused" $(ROOT_DIR)/../binutils/repo/configure \
		--target=m68k-unknown-elf \
		--disable-nls \
		--enable-gold=no \
		--enable-ld=yes \
		--prefix=$(OUTPUT)/root-cross
	cd $(OUTPUT)/$@ && $(MAKE)
	cd $(OUTPUT)/$@ && $(MAKE) install
	touch $@

gcc-cross-build-done-$(GCC_VERSION): binutils-cross-build-done-$(BINUTILS_VERSION)
	mkdir -p $(OUTPUT)/$@
	cd $(OUTPUT)/$@ && $(ROOT_DIR)/../gcc/repo/configure \
		--target=m68k-unknown-elf \
		--enable-languages=c \
		--disable-tls \
		--disable-libssp \
		--prefix=$(OUTPUT)/root-cross
	cd $(OUTPUT)/$@ && $(MAKE)
	cd $(OUTPUT)/$@ && $(MAKE) install
	touch $@
