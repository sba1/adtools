#
# Makefile to compile binutils cross
#
# Use SRC_DIR to alter the path of the source (default ../binutils)
# Use VERSION to specify the version (alters the name of the created drawer)
#

SRC_DIR=../binutils
VERSION=trunk
CROSS_BUILD_DIR=cross-$(VERSION)
NATIVE_BUILD_DIR=cross-$(VERSION)
PREFIX=/usr/local/amiga
REAL_SRC_DIR=$(realpath $(SRC_DIR))

all: cross

.PHONY: cross
cross:
	mkdir -p $(CROSS_BUILD_DIR)
	cd $(CROSS_BUILD_DIR); CFLAGS="-Wno-switch -Wno-unused" $(REAL_SRC_DIR)/configure \
									--target=ppc-amigaos \
									--prefix=$(PREFIX)
	make -C $(CROSS_BUILD_DIR)

native:
	mkdir -p $(NATIVE_BUILD_DIR)
	cd $(NATIVE_BUILD_DIR);  CFLAGS="-Wno-switch -Wno-unused" $(REAL_SRC_DIR)/configure \
											--target=ppc-amigaos \
											--host=ppc-amigaos \
											--prefix=/gcc
	make -C $(NATIVE_BUILD_DIR)

