#!/bin/bash -x

(cd packaging/deb/adtools-gcc && debuild -i -us -uc -b >/tmp/build.out)
