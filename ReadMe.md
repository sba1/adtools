The adtools project
===================

Introduction
------------

This is the Amiga developement tools project that host a number of tools
that can be used to develop applications for Amigaoid systems. Mostly,
the AmigaOS4 version is in a relatively good shape while this is probably
not the case for the other systems.

The main repo is still hosted on a SVN repository under
https://sf.net/projects/adtools. It uses the concept of vendor branches
but this is making quick progress newly impossible, so a new approach
is tested here.

In contrast, in this repository, build products that are based on other
projects (e.g. gcc) are not imported directly. Instead only the patches
that need to be applied to a given mainline (e.g. gcc 4.9) are directly
stored and maintained.

Patch management
----------------

A very naive patch management system that should simplify the management
of patches is included here. The scripts are situated in bin directory.
The scripts depend on Python.

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

