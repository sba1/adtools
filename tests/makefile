CC  = ppc-amigaos-gcc
CPP = ppc-amigaos-g++ -v

all: test-exceptions test-dynld

test-exceptions.o: test-exceptions.cpp
	$(CPP) -c $< -o $@  -ggdb

test-exceptions: test-exceptions.o
	$(CPP) $< -o $@ -ggdb -use-dynld

test-dynld: test-dynld.c
	$(CC) $< -o $@ -fPIC -use-dynld -o $@

test-thread: test-thread.cpp
	$(CPP) -ggdb -ffunction-sections -fdata-sections -MD $< -o $@.o -std=c++11 -c
	$(CPP) -ggdb $@.o -o $@ -std=c++11 -lpthread -Wl,-Map=$@.map,--cref -Wl,--gc-sections -Wl,--verbose -Wl,-T,test-thread-ldscript

clean:
	rm -Rf test-exceptions.o test-exceptions
