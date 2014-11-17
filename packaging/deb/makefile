# This make file builds the debian packages via docker and
# puts the results into the current directory

ROOT = $(realpath ../../)

all: source-packages

.PHONY: prepare-packages
prepare-packages:
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
.PHONY: source-packages
source-packages: prepare-packages
	dpkg-source -b adtools-sdk
	dpkg-source -b adtools-binutils

.PHONY: docker
docker:
	docker build -t adtools-debs .
