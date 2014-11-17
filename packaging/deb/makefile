# This make file builds the debian packages via docker and
# puts the results into the current directory

ROOT = $(realpath ../../)

all: source-packages

.PHONY: prepare-packages
prepare-packages: prepare-binutils prepare-gcc

.PHONY: prepare-binutils
prepare-binutils:
	rm -Rf adtools-binutils/patches
	cp -R $(ROOT)/binutils/2.23.2/patches adtools-binutils
	$(ROOT)/bin/adtget binutils 2.23.2
	rm -Rf adtools-binutils/binutils-2.23.2
	rm -Rf adtools-binutils/patched
	cd adtools-binutils && \
		tar xjf ../binutils-2.23.2.tar.bz2 && \
		mv binutils-2.23.2 patched && \
		cd patched && \
			git init && \
			git add . && \
			git apply ../patches/*.patch && \
			rm -Rf .git

.PHONY: prepare-gcc
prepare-gcc:
	rm -Rf adtools-gcc/patches
	cp -R $(ROOT)/gcc/4.9/patches adtools-gcc
	$(ROOT)/bin/adtget gcc 4.9
	rm -Rf adtools-gcc/gcc-4.9.1
	rm -Rf adtools-gcc/patched
	cd adtools-gcc && \
		tar xjf ../gcc-4.9.1.tar.bz2 && \
		mv gcc-4.9.1 patched && \
		cd patched && \
			git init && \
			git add . && \
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
