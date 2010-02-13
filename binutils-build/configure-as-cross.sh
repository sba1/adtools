#!/bin/bash
#
# Script for configuring binutils as cross compiler. Output is placed
# in the "cross" directory.
#
# TODO: Perhaps a tiny makefile would be more appropriate
#
mkdir -p cross
pushd cross
../../binutils/configure --target=ppc-amigaos --prefix=/usr/local/amiga
popd
