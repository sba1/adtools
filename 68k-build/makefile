ROOT_DIR=$(realpath .)

BINUTILS_VERSION=2.23.2
BINUTILS_SRC_DIR=../binutils/repo

GCC_SRC_DIR=../gcc/repo
GCC_VERSION:=$(shell cat $(GCC_SRC_DIR)/gcc/BASE-VER)

OUTPUT = $(ROOT_DIR)/output

all: binutils-cross-build-done-$(BINUTILS_VERSION)

binutils-cross-build-done-$(BINUTILS_VERSION):
	mkdir -p $(OUTPUT)/$@
	cd $(OUTPUT)/$@ && $(ROOT_DIR)/../binutils/repo/configure \
		--target=m68k-unknown-elf \
		--disable-nls \
		--enable-gold=no \
		--enable-ld=yes
	cd $(OUTPUT)/$@ && $(MAKE)