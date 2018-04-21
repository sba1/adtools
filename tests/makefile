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

################################################################################

.PHONY: run-all
run-all: \
	run-test-aos4-extensions-simple \
	run-test-baserel \
	run-test-baserel-o1

#
# Macro to insert a recipe for compiling plain tests that run on a qemu target.
# $(1) specifies some additional flags
#
define CC_PLAIN
	$(CC) -g -Wa,-me500 $(1) $< -nostdinc -nostdlib -fno-builtin -g -c -o $@.o
	ppc-amigaos-objdump -Sr  $@.o >$@.S
	$(CC) -g -Wa,-me500 $(1) $@.o -nostdinc -nostdlib -fno-builtin -g -o $@
endef

#
# Macro to insert targets and rules for executing a test
# executable via QEMU. The target is named run-$(1) and it
# depends on $(1).
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
# We first calculate the md5sums of the actual and expected output. If they match
# everything is fine, otherwise we employ wdiff to highlight the difference
	@echo compare $$<.actual $$<.expected
	if [ $$$$(md5sum $$<.actual $$<.expected | cut -d ' ' -f 1 | sort -u | wc -l) != '1' ]; then \
		wdiff -s $$<.expected $$<.actual; \
		false;\
	fi
endef

test-aos4-extensions-simple: test-aos4-extensions-simple.c common.h
	$(call CC_PLAIN,-O0)

$(eval $(call QEMU_RUN,test-aos4-extensions-simple))

test-baserel: test-baserel.c common.h
	$(call CC_PLAIN,-O0 -mbaserel)

$(eval $(call QEMU_RUN,test-baserel))

test-baserel-o1.c: test-baserel.c
	cp $< $@

test-baserel-o1: test-baserel-o1.c common.h
	$(call CC_PLAIN,-O1 -mbaserel)

$(eval $(call QEMU_RUN,test-baserel-o1))

################################################################################

clean:
	rm -Rf $(TESTS)
