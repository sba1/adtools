# Dockerfile for generating adtools packages for Cygwin
                           
FROM adtools         
                    
RUN apt-get update
RUN apt-get install -y --no-install-recommends \
	binutils \
	patch \
	gcc \
	subversion \
	build-essential \
	wget \
	debhelper \
	devscripts \
	texinfo \
	lhasa \
	libgmp-dev \
	libmpfr-dev \
	libmpc-dev \
	fakeroot \
	flex

# Build Cygwin compiler first
RUN mkdir -p /cygwin/src
WORKDIR /cygwin/src
ENV MIRROR_BASE http://cygwin.mirror.constant.com/
RUN wget ${MIRROR_BASE}/x86/release/binutils/binutils-2.24.51-5-src.tar.xz
RUN wget ${MIRROR_BASE}/x86/release/gcc/gcc-4.8.3-3-src.tar.xz

# Start with binutils
RUN tar -xJf binutils-2.24.51-5-src.tar.xz
WORKDIR /cygwin/src/binutils-2.24.51-5.src
RUN tar -xjf binutils-2.24.51.tar.bz2
WORKDIR /cygwin/src/binutils-2.24.51-5.src/binutils-2.24.51
RUN patch -p1 --dry-run <../2.24.51-ld-__dso_handle.patch
RUN ./configure \
	--target=i686-pc-cygwin \
	--enable-install-libiberty \
	--disable-gdb \
	--disable-libdecnumber \
	--disable-readline \
	--disable-sim
RUN make -j2
RUN make install

# Cont. with gcc
WORKDIR /cygwin/src
RUN tar -xJf gcc-4.8.3-3-src.tar.xz
WORKDIR /cygwin/src/gcc-4.8.3-3.src
RUN tar -xjf gcc-4.8.3.tar.bz2
WORKDIR /cygwin/src/gcc-4.8.3-3.src/gcc-4.8.3/
RUN find .. -name "*patch" | xargs -n1 -t patch -p1
RUN apt-get install -y --no-install-recommends \
	zlib1g-dev \
	less
RUN mkdir ../gcc-4.8.3-build
WORKDIR /cygwin/src/gcc-4.8.3-3.src/gcc-4.8.3-build

RUN wget ${MIRROR_BASE}/x86/release/cygwin/cygwin-1.7.32-1.tar.xz
RUN wget ${MIRROR_BASE}/x86/release/w32api-headers/w32api-headers-3.2.0-1.tar.xz
RUN wget ${MIRROR_BASE}/x86/release/w32api-runtime/w32api-runtime-3.2.0-1.tar.xz
RUN wget ${MIRROR_BASE}/x86/release/libiconv/libiconv-1.14-2.tar.bz2
RUN wget ${MIRROR_BASE}/x86/release/gmp/libgmp-devel/libgmp-devel-4.3.2-1.tar.bz2
RUN wget ${MIRROR_BASE}/x86/release/mpfr/libmpfr-devel/libmpfr-devel-3.1.2-1.tar.bz2
RUN wget ${MIRROR_BASE}/x86/release/mpclib/libmpc-devel/libmpc-devel-1.0.1-2.tar.bz2
RUN tar -xJf cygwin-1.7.32-1.tar.xz
RUN tar -xJf w32api-headers-3.2.0-1.tar.xz
RUN tar -xJf w32api-runtime-3.2.0-1.tar.xz
RUN tar -xjf libiconv-1.14-2.tar.bz2
RUN tar -xjf libgmp-devel-4.3.2-1.tar.bz2
RUN tar -xjf libmpfr-devel-3.1.2-1.tar.bz2
RUN tar -xjf libmpc-devel-1.0.1-2.tar.bz2
RUN mkdir -p /usr/local/i686-pc-cygwin
RUN cp -R usr/include /usr/local/i686-pc-cygwin
RUN cp -R usr/lib /usr/local/i686-pc-cygwin
RUN ../gcc-4.8.3/configure \
	--target=i686-pc-cygwin \
	--with-newlib \
	--enable-languages=c,c++
RUN make -j2
RUN make install

#
# Now really try to build the adtools cygwin packages
#
# Start creating necessary directories
#
RUN mkdir -p \
	/build/adtools/trunk \
	/build/adtools/branches\binutils \
	/build/adtools/branches\gcc \
	/build/adtools-build/binutils-build \
	/build/adtools-build/gcc-build

# Download sources
WORKDIR /build/adtools/trunk
RUN svn export svn://svn.code.sf.net/p/adtools/code/trunk/binutils-build
RUN svn export svn://svn.code.sf.net/p/adtools/code/trunk/gcc-build
RUN svn export svn://svn.code.sf.net/p/adtools/code/trunk/native-build
RUN svn export svn://svn.code.sf.net/p/adtools/code/trunk/packaging

WORKDIR /build/adtools/branches/binutils
RUN svn export svn://svn.code.sf.net/p/adtools/code/branches/binutils/2.23.2

WORKDIR /build/adtools/branches/gcc
RUN svn export svn://svn.code.sf.net/p/adtools/code/branches/gcc/4.9.x

# Now build and install adtools binutils
WORKDIR /build/adtools-build/binutils-build
RUN CFLAGS="-Wno-switch -Wno-unused" ../../adtools/branches/binutils/2.23.2/configure \
	--host=i686-pc-cygwin \
	--target=ppc-amigaos \
	--prefix=/usr/local/adtools
RUN make -j2
RUN make install

# Now build and install adtools gcc
WORKDIR /build/adtools-build/gcc-build
RUN ../../adtools/branches/gcc/4.9.x/configure \
	--host=i686-pc-cygwin \
	--target=ppc-amigaos \
	--prefix=/usr/local/adtools \
	--with-bugurl='http://sf.net/p/adtools' \
        --with-pkgversion='adtools build $(VERSION)' \
        --prefix=/usr/local/adtools \
	--enable-languages=c,c++  \
	--enable-haifa            \
	--enable-sjlj-exceptions  \
	--disable-libstdcxx-pch
RUN make -j2
RUN make install

# Original option found in cygport file of the gcc cygwin package
#RUN ../gcc-4.8.3/configure \
#	--target=i686-pc-cygwin \
#	--enable-shared \
#	--enable-shared-libgcc \
#	--enable-static \
#	--enable-version-specific-runtime-libs \
#	--with-dwarf2 \
#	--with-tune=generic \
#	--enable-languages=c,c++ \
#	--enable-graphite \
#	--enable-threads=posix \
#	--enable-libatomic \
#	--enable-libgomp \
#	--disable-libitm \
#	--enable-libquadmath \
#	--enable-libquadmath-support \
#	--enable-libssp \
#	--disable-java-awt \
#	--disable-symvers \
#	--with-gnu-ld \
#	--with-gnu-as \
#	--without-libiconv-prefix \
#	--without-libintl-prefix \
#	--with-system-zlib \
#	--enable-linker-build-id
