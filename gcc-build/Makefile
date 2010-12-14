#
# Makefile to compile cross
#
# Use SRC_DIR to alter the path of the source (default ../gcc)
# Use VERSION to specify the version (alters the name of the created drawer)
#
# when compiling 4.4.x or newer.
# 

SRC_DIR=../gcc
VERSION=trunk
DEST_DIR=cross-$(VERSION)
PREFIX=/usr/local/amiga
BUILD=i686-pc-linux-gnu ## for some reasons configure script of gcc 4.2.4 doesn't identify the correct build type

all: cross

.PHONY: cross
cross:
	mkdir -p cross-$(VERSION)
	cd cross-$(VERSION); ../$(SRC_DIR)/configure \
                      --with-bugurl='http://www.sf.net/projects/adtools' \
                      --with-pkgversion='adtools build $(VERSION)' \
											--target=ppc-amigaos \
											--prefix=$(PREFIX) \
											--enable-languages=c,c++  \
											--enable-haifa            \
											--enable-sjlj-exceptions  \
											--disable-libstdcxx-pch \
											--disable-tls
	make -C cross-$(VERSION)

.PHONY: native
native:
	mkdir -p native-$(VERSION)
	cd native-$(VERSION); ../$(SRC_DIR)/configure \
                      --with-bugurl='http://www.sf.net/projects/adtools' \
                      --with-pkgversion='adtools build $(VERSION)' \
											--host=ppc-amigaos \
											--build=$(BUILD) \
											--disable-nls \
											--target=ppc-amigaos \
											--prefix=/gcc \
											--enable-languages=c,c++  \
											--enable-haifa            \
											--enable-sjlj-exceptions  \
											--disable-libstdcxx-pch \
											--disable-tls
	make -C native-$(VERSION)
