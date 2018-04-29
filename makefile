#
# This makefile, for now does only little like building
# documentation.
#

GCC_SRC_DIR=gcc/repo
GCC_VERSION:=$(shell cat $(GCC_SRC_DIR)/gcc/BASE-VER)

.PHONY: all
all:

.PHONY: doc-build
doc-build:
	rm -Rf $@
	mkdir -p $@
	echo "@set version-GCC $(GCC_VERSION)" >$@/gcc-vers.texi
	echo "@set srcdir gcc/repo/gcc" >>$@/gcc-vers.texi
	echo "@set BUGURL https://github.com/sba1/adtools/issues" >>$@/gcc-vers.texi
	./bin/gild checkout gcc 8 --skip-patches
	makeinfo --plaintext -I gcc/repo/gcc/doc -I gcc/repo/gcc/doc/include -I $@ -o $@/gcc-orig.txt gcc/repo/gcc/doc/gcc.texi
	./bin/gild checkout gcc 8
	makeinfo --plaintext -I gcc/repo/gcc/doc -I gcc/repo/gcc/doc/include -I $@ -o $@/gcc.txt gcc/repo/gcc/doc/gcc.texi
	cd $@ && wdiff -n   -w $$'\033[30;41m' -x $$'\033[0m'   -y $$'\033[30;42m' -z $$'\033[0m'   gcc-orig.txt gcc.txt >gcc-changes.txt
