export PATH := $(shell pwd)/build/i686-elf-4.9.1-Linux-x86_64/bin:$(PATH)

QEMUFLAGS=-display curses
QEMUARGS=-kernel kernel/kernel.bin -initrd boot/boot.bin

all: kernel boot

test: all
	qemu-system-i386 $(QEMUARGS) $(QEMUFLAGS)

test_qemu_debug: all
	@echo in another terminal run: gdb
	qemu-system-i386 -S -s $(QEMUARGS) $(QEMUFLAGS)

test_cdrom: build/test.iso
	qemu-system-i386 -cdrom build/test.iso $(QEMUFLAGS)

test_bochs: build/test.iso
	bochs -qf .bochs.cfg

boot:
	$(MAKE) -C boot

kernel:
	$(MAKE) -C kernel

build/test.iso: all
	mkdir -p build/iso/boot/grub
	cp boot/boot.bin build/iso/boot/boot.bin
	cp kernel/kernel.bin build/iso/boot/kernel.bin
	cp .grub.cfg build/iso/boot/grub/grub.cfg
	grub-mkrescue -o build/test.iso build/iso

clean:
	$(MAKE) -C kernel clean
	$(MAKE) -C boot clean

.PHONY: all clean kernel boot test
