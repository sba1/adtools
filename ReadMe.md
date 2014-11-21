The adtools project
===================

Introduction
------------

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
repositotry, Instead only the patches that need to be applied to a given 
base version (e.g. stock gcc 4.9) are directly stored and maintained.

Patch management
----------------

A very naive patch management system that should simplify the management
of patches is included here. The scripts are situated in the ```bin```
directory. The scripts depend on Python.

* ```adtclone```: will fetch the external sources of all components into
 the respective ```repo``` directories. The checkout will not be affected.

* ```adtcheckout ```: will checkout for a specific component a specific 
 branch to the working directory of the ```repo``` directory and apply 
 the current patches for this branch. The result of this is what should 
 be used for compiling. It can also be used to adjust the order and 
 content of the patches e.g., using ```git rebase``` etc. For example,
 invoke
 ```
 $ adtcheckout gcc 4.9
 ```
 to checkout the version 4.9 branch of gcc and apply all adtools patches
 for this branch.

* ```adtgenpatch```: will generate the patches between the base checkout
 and the current HEAD of the repo. The patches are written to the
 ```patches``` directory of the respective component. For instance,
 invoke
 ```
 $ adtgenpatch gcc 4.9
 ```
 to generate the tracked changes for 4.9 branch of gcc. The patches will
 be located in ```gcc/4.9/patches```.

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
$ bin/adtcheckout gcc 4.9
```
Building is then a matter of entering
```
$ make -f native-build
```

The building should succeed, if all dependencies are met (e.g.,
```libgmp-dev```, ```libmpc-dev```, ```libmpfr-dev```, ```lha | lhasa```).
If you just need a cross-compiler then call the ```gcc-done``` target like
that:

```
$ make -C native-build gcc-done
```

### Packaging

Debian packaging is provided in ```packaging/deb```. There also some Docker
scripts, however, they may not work correctly at the moment.
