export PATH := $(shell pwd)/build/i686-elf-4.9.1-Linux-x86_64/bin:$(PATH)

QEMUFLAGS=-display curses

all: kernel

test: all
	qemu-system-i386 -kernel kernel/kernel.bin $(QEMUFLAGS)

kernel:
	$(MAKE) -C kernel

clean:
	$(MAKE) -C kernel clean

.PHONY: all clean kernel test
