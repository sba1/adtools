# Makefile to build the docker image

all:
	make -C ../deb
	mkdir -p repo
	cd repo && docker run adtools-debs | tar xvf -
	docker build -t adtools .

