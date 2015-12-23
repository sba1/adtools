Short:         GCC-based development toolchain for AmigaOS 4.x
Uploader:      mail@sebastianbauer.info (Sebastian Bauer)
Author:        GNU and adtools authors
Type:          dev/gcc
Architecture:  ppc-amigaos
Kurz:          GCC basierende Toolchain für AmigaOS 4.x
Requires:      OS 4.1
Version:       ${DIST_VERSION}

This archive includes native AmigaOS 4.1 compiles of binutils ${BINUTILS_VERSION}, gcc ${GCC_VERSION}, and
coreutils ${COREUTILS_VERSION} based on https://github.com/sba/sba1/adtools version ${DIST_VERSION}
commit ${ADTOOLS_COMMIT_SHA1}.

In order to install it on your Amiga, extract the archive to a destination of your
choice. Then establish a GCC: assignment to the extracted folder and add the contained
bin folder to the command search path
  1> ASSIGN GCC: <extracted folder>
  1> PATH GCC:bin add

Furthermore, you need to have an SDK: assign as in the original SDK.

This is a preliminary version and as such it will contain still many bugs. Please use
the issue tracker at https://github.com/sba1/adtools/issues for reporting bugs.

Note that the plan is to split the project and move the parts to separate subprojects
at https://github.com/adtools/. One other goal is to include the projects or updated
ones as part of one of the next AmigaOS SDK.
