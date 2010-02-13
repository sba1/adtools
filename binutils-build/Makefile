#
# Makefile to compile binutils
#
all: cross

.PHONY: cross
cross:
	mkdir -p cross
	cd cross; ../../binutils/configure --target=ppc-amigaos --prefix=/usr/local/amiga
	make -C cross	