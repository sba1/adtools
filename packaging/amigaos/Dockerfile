# Dockerfile for generating adtools amigaos packages
                           
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

#
# Now try to build the adtools amigaos packages
#
# Start creating necessary directories
#
RUN mkdir -p \
	/gcc \
	/build/adtools/trunk \
	/build/adtools/branches\binutils \
	/build/adtools/branches\gcc \
	/build/adtools-build/binutils-build \
	/build/adtools-build/gcc-build \
	/build/adtools-build/libs-build

# Download necessary libs
ENV GMP_ARCHIVE gmp-5.0.5/gmp-5.0.5.tar.bz2
ENV MPFR_ARCHIVE mpfr-3.1.2/mpfr-3.1.2.tar.bz2
ENV MPC_ARCHIVE mpc-0.9.tar.gz

# Build them
WORKDIR /build/adtools-build/libs-build
RUN wget -N ftp://ftp.gmplib.org/pub/${GMP_ARCHIVE}
RUN wget -N http://www.mpfr.org/${MPFR_ARCHIVE}
RUN wget -N http://www.multiprecision.org/mpc/download/${MPC_ARCHIVE}
RUN tar xjf `basename ${GMP_ARCHIVE}`
RUN tar xjf `basename ${MPFR_ARCHIVE}`
RUN tar xzf `basename ${MPC_ARCHIVE}`
RUN cd `basename ${GMP_ARCHIVE} .tar.bz2`  && ./configure --host=ppc-amigaos --prefix=/opt/adtools && make install
RUN cd `basename ${MPFR_ARCHIVE} .tar.bz2`  && ./configure --host=ppc-amigaos --with-gmp=/opt/adtools --prefix=/opt/adtools && make install
RUN cd `basename ${MPC_ARCHIVE} .tar.gz`  && ./configure --host=ppc-amigaos --with-gmp=/opt/adtools --prefix=/opt/adtools && make install

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
	--host=ppc-amigaos \
	--target=ppc-amigaos \
	--prefix=/gcc
RUN make -j2
RUN make install

# Now build and install adtools gcc
WORKDIR /build/adtools-build/gcc-build
RUN CPPFLAGS="-static" LDFLAGS="-static" ../../adtools/branches/gcc/4.9.x/configure \
	--host=ppc-amigaos \
	--target=ppc-amigaos \
	--prefix=/gcc \
	--with-bugurl='http://sf.net/p/adtools' \
        --with-pkgversion='adtools build $(VERSION)' \
	--enable-languages=c,c++  \
	--enable-haifa            \
	--enable-sjlj-exceptions  \
	--disable-libstdcxx-pch \
	--disable-nls \
	--disable-tls \
	--with-gmp=/opt/adtools \
	--with-mpfr=/opt/adtools \
        --with-mpc=/opt/adtools
	
RUN make -j2
RUN make install

WORKDIR /gcc/bin
RUN ppc-amigaos-strip *
RUN ln -sf ppc-amigaos-gcc-4.9.1 gcc
RUN ln -sf ppc-amigaos-gcc-4.9.1 ppc-amigaos-gcc
RUN ln -sf ppc-amigaos-g++ ppc-amigaos-c++
RUN ln -sf ppc-amigaos-g++ c++
RUN ln -sf ppc-amigaos-g++ g++
RUN ln -sf ld.bfd ld

WORKDIR /gcc/libexec/gcc/ppc-amigaos/4.9.1
RUN ppc-amigaos-strip \
	cc1 \
	cc1plus
# Merging the following with the previous segfaults
RUN ppc-amigaos-strip \
	lto1

# Switch back to the root
WORKDIR /
