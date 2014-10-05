# This make file builds the debian packages via docker and
# puts the results into the current directory

all:
	docker build -t adtools .
	docker run adtools | tar xvf -
