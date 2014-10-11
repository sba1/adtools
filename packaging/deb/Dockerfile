# Dockerfile for generating adtools Debian packages
                           
FROM debian:wheezy         
                    
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

# Download original gcc archives
RUN mkdir /build

WORKDIR  /build

RUN mkdir -p /build/adtools/trunk
RUN mkdir -p /build/adtools/branches

# Download sources
WORKDIR /build/adtools/trunk
RUN svn export svn://svn.code.sf.net/p/adtools/code/trunk/binutils-build
RUN svn export svn://svn.code.sf.net/p/adtools/code/trunk/gcc-build
RUN svn export svn://svn.code.sf.net/p/adtools/code/trunk/native-build
RUN svn export svn://svn.code.sf.net/p/adtools/code/trunk/packaging

WORKDIR /build/adtools/branches
RUN mkdir binutils gcc

WORKDIR /build/adtools/branches/binutils
RUN svn export svn://svn.code.sf.net/p/adtools/code/branches/binutils/2.23.2

WORKDIR /build/adtools/branches/gcc
RUN svn export svn://svn.code.sf.net/p/adtools/code/branches/gcc/4.9.x

# Download original sources
#RUN wget http://ftpmirror.gnu.org/gcc/gcc-4.9.1/gcc-4.9.1.tar.bz2
#RUN wget http://ftpmirror.gnu.org/binutils/binutils-2.23.2.tar.bz2

# Download deb files
#RUN svn export svn://svn.code.sf.net/p/adtools/code/trunk/packaging . --depth infinity

# Update SDK packaging
RUN rm -Rf /build/adtools/trunk/packaging/deb/adtools-sdk #
COPY adtools-sdk /build/adtools/trunk/packaging/deb/adtools-sdk

# Build SDK package
WORKDIR /build/adtools/trunk/packaging/deb/adtools-sdk
RUN debuild -i -us -uc -b

# Update debian packaging
RUN rm -Rf /build/adtools/trunk/packaging/deb/adtools-binutils
COPY adtools-binutils /build/adtools/trunk/packaging/deb/adtools-binutils

# Build Binutils package
WORKDIR /build/adtools/trunk/packaging/deb/adtools-binutils
RUN debuild -i -us -uc -b

# Install just built packages
WORKDIR /build/adtools/trunk/packaging/deb/
RUN dpkg --install *.deb

# Build GCC package
WORKDIR /build/adtools/trunk/packaging/deb/adtools-gcc

# Update debian packaging
RUN rm -Rf /build/adtools/trunk/packaging/deb/adtools-gcc
COPY adtools-gcc /build/adtools/trunk/packaging/deb/adtools-gcc

# Try to build the package, does not work yet
RUN debuild -j2 -i -us -uc -b

# Now copy all artifacts to a known directory
RUN mkdir /artifacts
WORKDIR /build/adtools/trunk/packaging/deb
RUN cp *.deb /artifacts
WORKDIR /artifacts
RUN dpkg-scanpackages ./ /dev/null | gzip >Packages.gz

# The default command that is executed when the container is started
# We simply generated a tar that the host should extract
CMD tar c .
