#!/bin/bash -x
#
# Simple shell script that is called in context of travis and that
# will build the current adtools-gcc packages.
#

(cd packaging/deb/adtools-gcc && debuild -j2 -i -us -uc -b >/tmp/build.out)
