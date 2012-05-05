CC  = ppc-amigaos-gcc
CPP = ppc-amigaos-g++

all: test-exceptions

test-exceptions.o: test-exceptions.cpp
	$(CPP) -c $< -o $@ 

test-exceptions: test-exceptions.o
	$(CPP) $< -o $@

clean:
	rm -Rf test-exceptions.o test-exceptions
