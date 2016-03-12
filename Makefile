export PATH := $(shell pwd)/build/i686-elf-4.9.1-Linux-x86_64/bin:$(PATH)

QEMUFLAGS=-display curses

all: kernel

test: all
	qemu-system-i386 -kernel kernel/kernel.bin $(QEMUFLAGS)

test_cdrom: build/test.iso
	qemu-system-i386 -cdrom build/test.iso $(QEMUFLAGS)

test_bochs: build/test.iso
	bochs -qf .bochs.cfg

kernel:
	$(MAKE) -C kernel

build/test.iso: kernel
	mkdir -p build/iso/boot/grub
	cp kernel/kernel.bin build/iso/boot/kernel.bin
	echo -e "menuentry \"HawthOS\" {\nmultiboot /boot/kernel.bin\n}" > build/iso/boot/grub/grub.cfg
	grub-mkrescue -o build/test.iso build/iso

clean:
	$(MAKE) -C kernel clean

.PHONY: all clean kernel test
