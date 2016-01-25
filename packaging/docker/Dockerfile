FROM debian:jessie

# Create and add the local repo
RUN mkdir /repo
COPY repo /repo
RUN echo deb file:/repo ./ >>/etc/apt/sources.list

RUN apt-get update
RUN apt-get install -y --no-install-recommends \
	wget \
	lhasa

RUN apt-get install -y --force-yes --no-install-recommends \
	adtools-binutils \
	adtools-sdk \
	adtools-gcc
