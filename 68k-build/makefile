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

includes-done: gcc-cross-build-done-$(GCC_VERSION)
	mkdir -p sources
	(cd sources && wget -N http://www.haage-partner.de/download/AmigaOS/NDK39.lha)
	(cd sources && lha xf NDK39.lha)
	rm -Rf $(OUTPUT)/root-cross/m68k-unknown-elf/include
	mv -f $(ROOT_DIR)/sources/NDK_3.9/Include/include_h $(OUTPUT)/root-cross/m68k-unknown-elf/include
	touch $@

clib2-done: gcc-cross-build-done-$(GCC_VERSION) includes-done
	mkdir -p sources
	(cd sources/clib2 && git pull) || git clone https://github.com/sba1/clib2 sources/clib2
	(cd sources/clib2 && PATH=$(OUTPUT)/root-cross/bin:$$PATH $(MAKE) -f GNUmakefile.68k CC=m68k-unknown-elf-gcc)
