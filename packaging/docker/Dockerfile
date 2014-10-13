FROM debian:wheezy

# Add backports
RUN echo deb http://ftp.debian.org/debian wheezy-backports main >>/etc/apt/sources.list

# Create and add the local repo
RUN mkdir /repo
COPY repo /repo
RUN echo deb file:/repo ./ >>/etc/apt/sources.list

RUN apt-get update
RUN apt-get install -y --no-install-recommends wget
RUN apt-get install -y --force-yes --no-install-recommends \
	adtools-binutils \
	adtools-sdk \
	adtools-gcc
