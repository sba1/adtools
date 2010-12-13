#
# Makefile to compile binutils cross
#
# Use SRC_DIR to alter the path of the source (default ../binutils)
# Use VERSION to specify the version (alters the name of the created drawer)
#

SRC_DIR=../binutils
VERSION=trunk
DEST_DIR=cross-$(VERSION)
PREFIX=/usr/local/amiga

all: cross

.PHONY: cross
cross:
	mkdir -p cross-$(VERSION)
	cd cross-$(VERSION); ../$(SRC_DIR)/configure \
											--target=ppc-amigaos \
											--prefix=$(PREFIX)
	make -C cross-$(VERSION)

native:
	mkdir -p native-$(VERSION)
	cd native-$(VERSION); ../$(SRC_DIR)/configure \
											--target=ppc-amigaos \
											--host=ppc-amigaos \
											--prefix=/gcc
	make -C native-$(VERSION)
