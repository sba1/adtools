CC  = ppc-amigaos-gcc
CPP = ppc-amigaos-g++ -v

XGCC_DIR := $(shell make -s -C ../native-build print-xg-dir)
XGCC := $(XGCC_DIR)/xgcc -B $(XGCC_DIR)

QEMU_PPC := qemu-system-ppc

TESTS = \
	test-dynld \
	test-exceptions \
	test-lineartags.o \
	test-std-string \
	test-thread \
	test-wchar

all: $(TESTS)

test-exceptions.o: test-exceptions.cpp
	$(CPP) -c $< -o $@  -ggdb

test-exceptions: test-exceptions.o
	$(CPP) $< -o $@ -ggdb -use-dynld

test-std-string: test-std-string.cpp
	$(CPP) $< -o $@ -std=c++11 -mcrt=clib2 #-U__STRICT_ANSI__

test-dynld: test-dynld.c
	$(CC) $< -o $@ -fPIC -use-dynld -o $@

test-thread: test-thread.cpp
	$(CPP) -ggdb -ffunction-sections -fdata-sections -MD $< -o $@.o -std=c++11 -c
	$(CPP) -ggdb $@.o -o $@ -std=c++11 -athread=native -Wl,-Map=$@.map,--cref -Wl,--gc-sections -Wl,--verbose
#	$(CPP) -ggdb $@.o -o $@ -std=c++11 -lpthread -Wl,-Map=$@.map,--cref -Wl,--gc-sections -Wl,--verbose -Wl,-T,test-thread-ldscript

test-thread-direct: test-thread.cpp ../gcc/repo/libgcc/gthr-amigaos-native.c
	$(CPP) test-thread.cpp ../gcc/repo/libgcc/gthr-amigaos-native.c -ggdb -ffunction-sections -fdata-sections -Wl,--gc-sections -std=c++11 -o $@

test-wchar: test-wchar.cpp
	$(CPP) test-wchar.cpp -std=c++11 -mcrt=clib2 -o $@ -H

test-tls: test-tls.cpp
	$(CPP) -g $< -o $@ ../gcc/repo/libgcc/gthr-amigaos-native.c -Wl,--cref -Wl,-M=$@.map

test-checktags.o: test-checktags.c
	$(XGCC) $< -c

test-call-once: test-call-once.cpp
	# This is only expected to work for gcc11+ since patch 0036
	# only applies to the gcc11 patches!
	$(CPP) -std=c++11 -athread=native -g $< -o $@

################################################################################

.PHONY: run-all
run-all: \
	run-test-aos4-extensions-simple \
	run-test-aos4-extensions-simple-o1 \
	run-test-aos4-extensions-simple-o3 \
	run-test-baserel \
	run-test-baserel-o1 \
	run-test-baserel-o3 \
	run-test-call-once

#
# Macro to insert a recipe for compiling plain tests that run on a qemu target.
# $(1) specifies some additional flags
#
define CC_PLAIN
	$(XGCC) -g -Wa,-me500 $(1) $< -nostdinc -nostdlib -fno-builtin -g -c -o $@.o
	ppc-amigaos-objdump -Sr  $@.o >$@.S
	$(XGCC) -g -Wa,-me500 $(1) $@.o -nostdinc -nostdlib -fno-builtin -g -o $@
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
	{ sleep 1; echo q; } | $(QEMU_PPC) -M ppce500 -kernel $$< -serial file:$$<.actual -nographic -monitor stdio >/dev/null || true
# Compare expected vs. actual, and if it differs highlight difference.
# We first calculate the md5sums of the actual and expected output. If they match
# everything is fine, otherwise we employ wdiff to highlight the difference
	@echo compare $$<.actual $$<.expected
	if [ $$$$(md5sum $$<.actual $$<.expected | cut -d ' ' -f 1 | sort -u | wc -l) != '1' ]; then \
		wdiff -s $$<.expected $$<.actual; \
		false;\
	fi
endef

################################################################################

# Pattern rule to prepare copies for different optimization levels
test-%-o1.c : test-%.c
	cp $< $@

test-%-o3.c : test-%.c
	cp $< $@

################################################################################

#
# Generate different falvors of simple tests that are executed on a qemu-based
# machine.
#
define QEMU_TARGETS
$(1): $(1).c common.h
	$$(call CC_PLAIN,-O0 $(2))

$(1)-o1: $(1)-o1.c common.h
	$$(call CC_PLAIN,-O1 $(2))

$(1)-o3: $(1)-o3.c common.h
	$$(call CC_PLAIN,-O3 $(2))

# Add the test to our TESTS macro
TESTS += $(1) $(1)-o1 $(1)-o3
endef

################################################################################

$(eval $(call QEMU_TARGETS,test-aos4-extensions-simple,))

$(eval $(call QEMU_RUN,test-aos4-extensions-simple))

$(eval $(call QEMU_RUN,test-aos4-extensions-simple-o1))

$(eval $(call QEMU_RUN,test-aos4-extensions-simple-o3))

################################################################################

$(eval $(call QEMU_TARGETS,test-baserel,-mbaserel))

$(eval $(call QEMU_RUN,test-baserel))

$(eval $(call QEMU_RUN,test-baserel-o1))

$(eval $(call QEMU_RUN,test-baserel-o3))

################################################################################

$(eval $(call QEMU_TARGETS,test-baserel-large,-mbaserel))

$(eval $(call QEMU_RUN,test-baserel-large))

################################################################################

.PHONY: clean
clean:
	rm -Rf \
		$(TESTS) \
		$(TESTS:%=%.o) \
		$(TESTS:%=%.S) \
		$(TESTS:%=%-o1.c) \
		$(TESTS:%=%-o3.c) \
		*.actual \
		*.d \
		*.expected
