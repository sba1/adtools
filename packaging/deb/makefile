# This make file builds the debian packages via docker and
# puts the results into the current directory

ROOT = $(realpath ../../)

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

GCC_ARCHIVE_NAME = $(shell basename $(shell $(ROOT)/bin/gild get gcc 5 --print-url-only))
GCC_DIR = $(basename $(basename $(GCC_ARCHIVE_NAME)))

.PHONY: prepare-gcc
prepare-gcc:
	rm -Rf adtools-gcc/patches
	cp -R $(ROOT)/gcc/5/patches adtools-gcc
	$(ROOT)/bin/gild get gcc 5
	rm -Rf adtools-gcc/$(GCC_DIR)
	rm -Rf adtools-gcc/patched
	cd adtools-gcc && \
		tar xzf ../$(GCC_ARCHIVE_NAME) && \
		mv $(GCC_DIR) patched && \
		cd patched && \
			git init && \
			git apply ../patches/*.patch && \
			rm -Rf .git

.PHONY: source-packages
source-packages: prepare-packages
	dpkg-source -b adtools-sdk
	dpkg-source -b adtools-binutils
	dpkg-source -b adtools-gcc

.PHONY: docker
docker:
	docker build -t adtools-debs .
