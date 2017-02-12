#!/bin/bash -x
#
# Simple shell script that is called in context of travis and that
# will build the current native adtools package.
#

make -C native-build CROSS_IS_PRESENT=1 &>/tmp/build.out
