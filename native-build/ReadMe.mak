Short:         GCC-based development toolchain for AmigaOS 4.x
Uploader:      mail@sebastianbauer.info (Sebastian Bauer)
Author:        GNU and adtools authors
Type:          dev/gcc
Architecture:  ppc-amigaos
Kurz:          GCC-basierte Toolchain für AmigaOS 4.x
Requires:      OS 4.1
Version:       ${DIST_VERSION}

This archive includes native AmigaOS 4.1 compiles of
 * binutils ${BINUTILS_VERSION},
 * gcc ${GCC_VERSION}${GCC_DEV_PHASE}, and
 * coreutils ${COREUTILS_VERSION}
based on https://github.com/sba/sba1/adtools version ${DIST_VERSION}
commit ${ADTOOLS_COMMIT_SHA1}.

In order to install it on your Amiga, extract the archive to a destination of your
choice. Then establish a GCC: assignment to the extracted folder and add the contained
bin folder to the command search path
  1> ASSIGN GCC: <extracted folder>
  1> PATH GCC:bin add

If you want that various short cuts for the binaries are represented by soft links on
you local harddisk, try the RestoreLinks script:
  1> cd <extracted folder>
  1> EXECUTE RestoreLinks

Furthermore, you need to have an SDK: assign as in the original SDK.

Note that if you use the APPDIR: feature you should flush its contents. Otherwise, you
may observe unexpected behaviour. Most easily this can be achieved by entering
  1> delete APPDIR:#?

This is a preliminary version and as such it will contain still many bugs. Please use
the issue tracker at https://github.com/sba1/adtools/issues for reporting bugs.

Note that the plan is to split the project and move the parts to separate subprojects
at https://github.com/adtools/. One other goal is to include the projects or updated
ones as part of one of the next AmigaOS SDK.

About the C++ support
=====================

C++-support using clib2 clib (enabled via -mcrt=clib2) is much better than with
the newlib clib at the moment. If you encounter any errors when compiling C++
projects using newlib, also try clib2. To be successful, you should use the
accompanying clib2 release archive ${CLIB2_RELEASE_ARCHIVE_NAME} and install its
contents into the SDK: folder. You can find this (unofficial) archive at
https://dl.bintray.com/sba1/adtools-native/.

Alternatively to clib2, there is clib4, which is a fork from the original
clib2. The release archive is ${CLIB4_RELEASE_ARCHIVE_NAME}.

Also for C++, it is recommended not to use the shared objects feature (aka
dynload) for now. The reason is that the C++-ABI may change in the future.
Lastly, you should link the final executable using the --athread=native
option if you use anything from libstdc++.

Changes of the AmigaOS version
==============================

In the doc folder, there is some usual gcc documentation provided. This is actually
a diff to the original documentation, so AmigaOS-relevant changes are easily
recognizable.

Most notable changes are:
 * --athread, -mbaserel, --mcrt, -mno-baserel, and --use-dyn-lib driver options
 * baserel_restore, checktags, libcall, libcall2, linearvarargs function attributes
 * force_no_baserel variable attribute
 * tagtype enum attribute
