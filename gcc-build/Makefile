#
# Makefile to compile cross
#
# Use SRC_DIR to alter the path of the source (default ../gcc)
# Use VERSION to specify the version (alters the name of the created drawer)
#

SRC_DIR=../gcc
VERSION=trunk
DEST_DIR=cross-$(VERSION)
PREFIX=/usr/local/amiga

all: cross

.PHONY: cross
cross:
	mkdir -p cross-$(VERSION)
	cd cross-$(VERSION); ../$(SRC_DIR)/configure \
											--target=ppc-amigaos \
											--prefix=$(PREFIX) \
											--enable-languages=c,c++  \
											--enable-haifa            \
											--enable-sjlj-exceptions  \
											--disable-libstdcxx-pch \
											--disable-tls
	make -C cross-$(VERSION)
