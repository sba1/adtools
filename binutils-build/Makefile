#
# Makefile to compile binutils
#
SRC_DIR=../../binutils

all: cross

.PHONY: cross
cross:
	mkdir -p cross
	cd cross; $(SRC_DIR)/configure --target=ppc-amigaos --prefix=/usr/local/amiga
	make -C cross
