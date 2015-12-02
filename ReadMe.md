The adtools project
===================

[![Build Status](https://travis-ci.org/sba1/adtools.svg?branch=master)](https://travis-ci.org/sba1/adtools)

This is the Amiga developement tools project that host a number of tools
that can be used to develop applications for AmigaOS and Amigaoid
systems. At the moment only the version for the latest AmigaOS version
(4.x) is in a relatively good shape while this is probably not the case
for the other systems.

The main repo is still hosted on a SVN repository under
https://sf.net/projects/adtools. It uses the concept of vendor branches
but this is making quick progress nearly impossible, so a new approach
is tested here.

In contrast to the original approch, build products that are based on 
other projects (e.g. gcc) are not imported directly into this 
repository. Instead only the patches that need to be applied to a given 
base version (e.g. stock gcc 5) are directly stored and maintained.

Installation
------------

### AmigaOS
No binaries for AmigaOS are currently provided. Refer to the Building section how to build one yourself.

### Debian-based Linux distributions

Debian packages are generated automatically for the amd64 architecture. You can integrate them in
your Debian installation by adding

```
 deb http://dl.bintray.com/sba1/adtools-deb /
```

to your ```/etc/apt/sources.list``` file. E.g., by 

```
$ echo "deb http://dl.bintray.com/sba1/adtools-deb /" | sudo tee -a /etc/apt/sources.list
```

Note that the packages are currently not signed. Installation is then as easy as typing

```
$ aptitude install adtools-gcc
```

This will also install the SDK and binutils due to the dependencies.


Patch management
----------------

A very naive patch management system that should simplify the management
of patches is included here. The scripts are situated in the ```bin```
directory. The scripts depend on Python.

* ```adtlist```: lists available components and branches. For instance
 ```
 $ adtlist
 binutils 2.23.2
 coreutils 5.2
 gcc 4.9
 gcc 5
 ```
 shows that there are three components ```binutils```, ```coreutils```, and
 ```gcc```.

* ```adtclone```: will fetch the external sources of all components into
 the respective ```repo``` directories. The checkout will not be affected.

* ```adtcheckout ```: will checkout for a specific component a specific 
 branch to the working directory of the ```repo``` directory and apply 
 the current patches for this branch. The result of this is what should 
 be used for compiling. It can also be used to adjust the order and 
 content of the patches e.g., using ```git rebase``` etc. For example,
 invoke
 ```
 $ adtcheckout gcc 5
 ```
 to checkout the version 5 branch of gcc and apply all adtools patches
 for this branch.

* ```adtgenpatch```: will generate the patches between the base checkout
 and the current HEAD of the repo. The patches are written to the
 ```patches``` directory of the respective component. For instance,
 invoke
 ```
 $ adtgenpatch gcc 5
 ```
 to generate the tracked changes for 5 branch of gcc. The patches will
 be located in ```gcc/5/patches```.

Building
--------

### Local

The local build is suitable when no packaging should be done. The easiest
approch involves invoking the ```makefile``` provided in the
```native-build``` folder. The procedure currently assumes that the sources
have previously been checked out and that the patches have been applied.
This can be done by:
```
$ bin/adtclone
$ bin/adtcheckout binutils 2.23.2
$ bin/adtcheckout coreutils 5.2
$ bin/adtcheckout gcc 5
```
Building is then a matter of entering
```
$ make -C native-build
```

The building should succeed, if all dependencies are met (e.g.,
```libgmp-dev```, ```libmpc-dev```, ```libmpfr-dev```, ```lha | lhasa```).
If you just need a cross-compiler then call the ```gcc-done``` target like
that:

```
$ make -C native-build gcc-done
```

In this case, you also don't need to checkout the ```coreutils```
component.

### Packaging

Debian packaging is provided in ```packaging/deb```. There also some Docker
scripts, however, they may not work correctly at the moment.
