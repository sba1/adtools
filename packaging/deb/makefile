# This make file builds the debian packages via docker and
# puts the results into the current directory

ROOT = $(realpath ../../)

GCC_BRANCH_NAME=5

all: source-packages

#
# Prepare all packages in the appropriate patched folder
#
.PHONY: prepare-packages
prepare-packages: prepare-binutils prepare-gcc

.PHONY: prepare-binutils
prepare-binutils:
	rm -Rf adtools-binutils/patches
	cp -R $(ROOT)/binutils/2.23.2/patches adtools-binutils
	$(ROOT)/bin/gild get binutils 2.23.2
	rm -Rf adtools-binutils/binutils-2.23.2
	rm -Rf adtools-binutils/patched
	cd adtools-binutils && \
		tar xjf ../binutils-2.23.2.tar.bz2 && \
		mv binutils-2.23.2 patched && \
		cd patched && \
			git init && \
			git apply ../patches/*.patch && \
			rm -Rf .git

GCC_ARCHIVE_NAME = $(shell basename $(shell $(ROOT)/bin/gild get gcc $(GCC_BRANCH_NAME) --print-url-only))
GCC_ARCHIVE_TAR_FILTER = $(subst .gz,z,$(subst .xz,J,$(suffix $(GCC_ARCHIVE_NAME))))
GCC_DIR = $(basename $(basename $(GCC_ARCHIVE_NAME)))

.PHONY: prepare-gcc
prepare-gcc:
	rm -Rf adtools-gcc/patches
	cp -R $(ROOT)/gcc/$(GCC_BRANCH_NAME)/patches adtools-gcc
	$(ROOT)/bin/gild get gcc $(GCC_BRANCH_NAME)
	rm -Rf adtools-gcc/$(GCC_DIR)
	rm -Rf adtools-gcc/patched
	cd adtools-gcc && \
		tar x$(GCC_ARCHIVE_TAR_FILTER)f ../$(GCC_ARCHIVE_NAME) && \
		mv $(GCC_DIR) patched && \
		cp $(ROOT)/gcc-build/features.mk debian && \
		cd patched && \
			git init && \
			git apply ../patches/*.patch && \
			rm -Rf .git
	$(MAKE) -C $(ROOT)/native-build downloads-done-clib2
	cp -R $(ROOT)/native-build/downloads/clib2 adtools-gcc/patched
	rm -Rf adtools-gcc/patched/clib2/.git

.PHONY: source-packages
source-packages: prepare-packages
	dpkg-source -b adtools-sdk
	dpkg-source -b adtools-binutils
	dpkg-source -b adtools-gcc

.PHONY: docker
docker:
	docker build -t adtools-debs .
