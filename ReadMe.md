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
base version (e.g. stock gcc 6) are directly stored and maintained.

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

A very naive patch management system called ```gild``` that should simplify the
management of patches has been developed in context of this project. In the
meantime, ```gild``` became a tiny project of its own and it is located at
http://github.com/sba1/gild. It is linked to this project using submodules
feature of git.

So in order to follow the build instructions, you need to make sure that the
```gild``` directory is populated:

```
$ git submodule init
$ git submodule update
````
With this and the softlink ```bin/gild``` you have access to the following
commands:


* ```gild list```: lists available components and branches. For instance
 ```
 $ gild list
 binutils 2.23.2
 coreutils 5.2
 gcc 4.9
 gcc 5
 gcc 6
 ```
 shows that there are three components ```binutils```, ```coreutils```,
 and ```gcc```

* ```gild clone```: will fetch the external sources of all components into
 the respective ```repo``` directories. The checkout will not be affected.

* ```gild checkout ```: will checkout for a specific component a specific
 branch to the working directory of the ```repo``` directory and apply
 the current patches for this branch. The result of this is what should
 be used for compiling. It can also be used to adjust the order and
 content of the patches e.g., using ```git rebase``` etc. For example,
 invoke
 ```
 $ gild checkout gcc 6
 ```
 to checkout the version 6 branch of gcc and apply all adtools patches
 for this branch.

 You should also invoke this command if you want to reapply the current
 set of patches (e.g., after pulling changed patch sets)

* ```gild genpatch```: will generate the patches between the base checkout
 and the current HEAD of the repo. The patches are written to the
 ```patches``` directory of the respective component. For instance,
 invoke
 ```
 $ gild genpatch gcc 6
 ```
 to generate the tracked changes for 6 branch of gcc. The patches will
 be located in ```gcc/6/patches```.

Building
--------

### Local

The local build is suitable when no packaging should be done. The easiest
approch involves invoking the ```makefile``` provided in the
```native-build``` folder. The procedure currently assumes that the sources
have previously been checked out and that the patches have been applied.
This can be done by:
```
$ bin/gild clone
$ bin/gild checkout binutils 2.23.2
$ bin/gild checkout coreutils 5.2
$ bin/bild checkout gcc 6
```
Building is then a matter of entering
```
$ make -C native-build
```

The building should succeed, if all dependencies are met (e.g.,
```libgmp-dev```, ```libmpc-dev```, ```libmpfr-dev```, ```lha | lhasa```).
If you just need a cross-compiler then call the ```gcc-cross``` target like
that:

```
$ make -C native-build gcc-cross
```

In this case, you also don't need to checkout the ```coreutils```
component. In order to use the cross compiler, add the ```root-cross/bin```
path to your ```PATH``` variable, e.g., like this:

```
$ export PATH=$PATH:$(pwd)/root-cross/bin
```

### Packaging

Debian packaging is provided in ```packaging/deb```. There also some Docker
scripts, however, they may not work correctly at the moment.
