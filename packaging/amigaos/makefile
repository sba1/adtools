all:
	make -C ../docker
	docker build -t adtools-amigaos .
	docker run adtools-amigaos tar c gcc | bzip2 >gcc.tar.bz2
