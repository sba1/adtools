The adtools project
===================

[![Build Status](https://travis-ci.org/sba1/adtools.svg?branch=master)](https://travis-ci.org/sba1/adtools)
[![DL](https://api.bintray.com/packages/sba1/adtools-native/adtools/images/download.svg)](https://bintray.com/sba1/adtools-native/adtools/_latestVersion#files)

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

An lha archive with current binaries can be found at https://dl.bintray.com/sba1/adtools-native.

In order to install it on your Amiga, extract the archive to a destination of your
choice. Then establish a GCC: assignment to the extracted folder and add the contained
```bin``` folder to the command search path

```
 1> ASSIGN GCC: <extracted folder>
 1> PATH GCC:bin add
```

Furthermore, you need to have an ```SDK:``` assign as in the original SDK.

Note that if you use the ```APPDIR:``` feature you should flush its contents. Otherwise,
you may observe unexpected behaviour. Most easily this can be achieved by entering

```
 1> delete APPDIR:#?
```


### Debian-based Linux distributions

Debian packages are generated automatically for the amd64 architecture. If not already
done, add the Bintray key that is used to sign the package to your installation, e.g., via:

```
apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 379CE192D401AB61
```

Then insert

```
 deb http://dl.bintray.com/sba1/adtools-deb /
```

to your ```/etc/apt/sources.list``` file. For instance, enter:

```
$ echo "deb http://dl.bintray.com/sba1/adtools-deb /" | sudo tee -a /etc/apt/sources.list
```

Installation is then as easy as typing

```
$ aptitude install adtools-binutils adtools-sdk adtools-gcc
```

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
With this, the softlink ```bin/gild``` and ```bin``` being in your command
line path, you have access to the following commands:


* ```gild list```: lists available components and branches. For instance
 ```
 $ gild list
 binutils 2.23.2
 coreutils 5.2
 gcc 4.9
 gcc 5
 gcc 6
 gcc 8
 ```
 shows that there are three components ```binutils```, ```coreutils```,
 and ```gcc```

* ```gild clone```: will fetch the external sources of all components into
 the respective ```repo``` directories. The checkout will not be affected.

* ```gild checkout```: will checkout for a specific component a specific
 branch to the working directory of the ```repo``` directory and apply
 the current patches for this branch. The result of this is what should
 be used for compiling. It can also be used to adjust the order and
 content of the patches e.g., using ```git rebase``` etc. For example,
 invoke
 ```
 $ gild checkout gcc 8
 ```
 to checkout the version 8 branch of gcc and apply all adtools patches
 for this branch. The gild tool will attempt a shallow clone of the
 remote repository if it doesn't exist locally.

 You should also invoke this command if you want to reapply the current
 set of patches (e.g., after pulling changed patch sets).

* ```gild genpatch```: will generate the patches between the base checkout
 and the current HEAD of the repo. The patches are written to the
 ```patches``` directory of the respective component. For instance,
 invoke
 ```
 $ gild genpatch gcc 8
 ```
 to generate the tracked changes for 8 branch of gcc. The patches will
 be located in ```gcc/8/patches```.

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
$ bin/gild checkout gcc 8
```
You can also try ```bin/gild checkout gcc 6``` but this produces the more
experimental version of gcc 6. Building is then a matter of entering
```
$ make -C native-build
```

Building requires some dependencies:
- libgmp-dev
- libmpc-dev
- libmpfr-dev
- lha (NOT lhasa. Instead, use: https://github.com/jca02266/lha)
- texinfo
- flex
- bison
- python3
- python3-mako

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

Note that you can change where the cross toolchain is located via the
```CROSS_PREFIX``` macro. For instance,

```
$ make -C native-build gcc-cross CROSS_PREFIX=/opt/adtools
```
would install the toolchain into ```/opt/adtools``` directory. Note that
the build process will write to this directory.

### Packaging

#### For AmigaOS

For creating an AmigaOS distribution archive, the ```makefile``` in the
```native-build``` folder is used as well. One prerequiste is that you
provide the current user access to a ```/gcc``` folder, e.g., via
```
 $ su
 $ mkdir /gcc
 $ chown <user> /gcc
```

Then, being in the ```native-build``` folder, enter

```
 $ make native-install
...
 $ make native-dist
...
 $ make clib2-dist
...
```

This will write some files into ```/gcc``` folder and create the
distribution archives suitable for ```lha``` for the entire toolchain
inclusive a custom archive for the clib2 static link library. List them
via
```
 $ ls *.lha
adtools-os4-20180405-458.lha  adtools-os4-clib2-20180405-458.lha
```

#### For Debian-based distributions

Debian packaging is provided in ```packaging/deb```. There also some Docker
scripts, however, they may not work correctly at the moment.
