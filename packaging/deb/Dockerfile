# Dockerfile for generating adtools Debian packages
FROM debian:jessie

RUN apt-get update
RUN apt-get install -t jessie -y --no-install-recommends \
	binutils \
	build-essential \
	debhelper \
	devscripts \
	fakeroot \
	flex \
	gcc \
	lhasa \
	libgmp-dev \
	libmpc-dev \
	libmpfr-dev \
	patch \
	subversion \
	texinfo \
	wget

# Prepare files
RUN mkdir /build
COPY . /build/
WORKDIR  /build

# Extract
RUN find -maxdepth 1 -name '*.dsc' | xargs -n 1 dpkg-source -x

# Create the packages
RUN cd adtools-sdk* && debuild -i -us -uc -b
RUN cd adtools-binutils* && debuild -i -us -uc -b

# Install the adtools-sdk dependency
RUN dpkg --install adtools-sdk_*.deb
RUN dpkg --install adtools-binutils*.deb

RUN cd adtools-clib2* && debuild -i -us -uc -b
RUN dpkg --install adtools-clib*.deb

RUN cd adtools-gcc* && debuild -i -us -uc -b

# Now copy all artifacts to a known directory
RUN mkdir /artifacts
RUN cp *.deb /artifacts
WORKDIR /artifacts
RUN dpkg-scanpackages ./ /dev/null | gzip >Packages.gz

# The default command that is executed when the container is started
# We simply generated a tar that the host should extract
CMD tar c .
