#
# Makefile to compile cross
#

SRC_DIR=../../gcc

all: cross

.PHONY: cross
cross:
	mkdir -p cross
	cd cross; $(SRC_DIR)/configure \
											--target=ppc-amigaos \
											--prefix=/usr/local/amiga \
											--enable-languages=c,c++  \
											--enable-haifa            \
											--enable-sjlj-exceptions  \
											--disable-libstdcxx-pch
	make -C cross
