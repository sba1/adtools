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
CROSS_BUILD_DIR=cross-$(VERSION)
NATIVE_BUILD_DIR=native-$(VERSION)
PREFIX=/usr/local/amiga
BUILD=i686-pc-linux-gnu ## for some reasons configure script of gcc 4.2.4 doesn't identify the correct build type
REAL_SRC_DIR=$(realpath $(SRC_DIR))

all: cross

.PHONY: cross
cross:
	mkdir -p $(CROSS_BUILD_DIR)
	cd $(CROSS_BUILD_DIR); $(REAL_SRC_DIR)/configure \
                      --with-bugurl='http://sf.net/p/adtools' \
                      --with-pkgversion='adtools build $(VERSION)' \
											--target=ppc-amigaos \
											--prefix=$(PREFIX) \
											--enable-languages=c,c++  \
											--enable-haifa            \
											--enable-sjlj-exceptions  \
											--disable-libstdcxx-pch \
											--disable-tls # \
#											--enable-checking=gc
	make -C $(CROSS_BUILD_DIR)

.PHONY: native
native:
	mkdir -p $(NATIVE_BUILD_DIR)
	cd $(NATIVE_BUILD_DIR); LDFLAGS="-lunix" $(REAL_SRC_DIR)/configure \
                      --with-bugurl='http://sf.net/p/adtools' \
                      --with-pkgversion='adtools build $(VERSION)' \
											--host=ppc-amigaos \
											--target=ppc-amigaos \
											--disable-nls \
											--prefix=/gcc \
											--enable-languages=c,c++  \
											--enable-haifa            \
											--enable-sjlj-exceptions  \
											--disable-libstdcxx-pch \
											--with-gmp=$(LIB_PATH) \
											--with-mpfr=$(LIB_PATH) \
											--with-mpc=$(LIB_PATH) \
											--disable-tls
	make -C $(NATIVE_BUILD_DIR)
