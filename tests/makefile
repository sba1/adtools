CC  = ppc-amigaos-gcc
CPP = ppc-amigaos-g++ -v

all: test-exceptions test-dynld

test-exceptions.o: test-exceptions.cpp
	$(CPP) -c $< -o $@  -ggdb

test-exceptions: test-exceptions.o
	$(CPP) $< -o $@ -ggdb -use-dynld

test-dynld: test-dynld.c
	$(CC) $< -o $@ -fPIC -use-dynld -o $@

clean:
	rm -Rf test-exceptions.o test-exceptions
