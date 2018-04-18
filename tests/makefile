CC  = ppc-amigaos-gcc
CPP = ppc-amigaos-g++ -v

TESTS = \
	test-dynld \
	test-exceptions \
	test-std-string \
	test-thread \
	test-wchar

all: $(TESTS)

test-exceptions.o: test-exceptions.cpp
	$(CPP) -c $< -o $@  -ggdb

test-exceptions: test-exceptions.o
	$(CPP) $< -o $@ -ggdb -use-dynld

test-std-string: test-std-string.c
	$(CPP) $< -o $@ -std=c++11 -U__STRICT_ANSI__

test-dynld: test-dynld.c
	$(CC) $< -o $@ -fPIC -use-dynld -o $@

test-thread: test-thread.cpp
	$(CPP) -ggdb -ffunction-sections -fdata-sections -MD $< -o $@.o -std=c++11 -c
	$(CPP) -ggdb $@.o -o $@ -std=c++11 -lpthread -Wl,-Map=$@.map,--cref -Wl,--gc-sections -Wl,--verbose -Wl,-T,test-thread-ldscript

test-wchar: test-wchar.cpp
	$(CPP) test-wchar.cpp -std=c++11 -mcrt=clib2 -o $@ -H

test-aos4-extensions-simple: test-aos4-extensions-simple.c common.h
	$(CC) -Wa,-me500 -O0 $< -nostdinc -nostdlib -fno-builtin -o $@

#
# Macro to insert targets and rules for executing a test
# executable via QEMU.
#
# We will force the virtual machine to quit after one second.
#
define QEMU_RUN
.PHONY: run-$(1)
run-$(1): $(1)
# Extract expected stdout
	<$$<.c ./extract-stdout.py >$$<.expected
# Run the executable via qemu for maximal one second, catch the serial output
	{ sleep 1; echo q; } | qemu-system-ppc -M ppce500 -kernel $$< -serial file:$$<.actual -nographic -monitor stdio >/dev/null || true
# Compare expected vs. actual, and if it differs highlight difference.
	@echo compare $$<.actual $$<.expected
	if [ $$$$(md5sum $$<.actual $$<.expected | cut -d ' ' -f 1 | sort -u | wc -l) != '1' ]; then \
		wdiff -s $$<.expected $$<.actual; \
		false;\
	fi
endef

$(eval $(call QEMU_RUN,test-aos4-extensions-simple))

test-baserel: test-baserel.c common.h
	$(CC) -g -Wa,-me500 -O0 $< -nostdinc -nostdlib -fno-builtin -g -mbaserel -c -o $@.o
	ppc-amigaos-objdump -Sr  $@.o >$@.S
	$(CC) -g -Wa,-me500 -O0 $@.o -nostdinc -nostdlib -fno-builtin -g -mbaserel -o $@

clean:
	rm -Rf $(TESTS)
