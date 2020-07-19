TOOLCHAIN=i686-elf-5.2.0-Linux-x86_64
export PATH := $(shell pwd)/build/$(TOOLCHAIN)/bin:$(PATH)

QEMUFLAGS=-display curses -serial mon:stdio -monitor telnet::45454,server,nowait
QEMUARGS=-kernel kernel/kernel.bin -initrd service/boot/boot.bin,service/ping/ping.bin,service/keyboard/keyboard.bin

all: kernel services

test: all
	qemu-system-i386 $(QEMUARGS) $(QEMUFLAGS)

test_qemu_debug: all
	@echo in another terminal run: gdb
	qemu-system-i386 -S -s $(QEMUARGS) $(QEMUFLAGS)

test_cdrom: build/test.iso
	qemu-system-i386 -cdrom build/test.iso $(QEMUFLAGS)

test_bochs: build/test.iso
	bochs -qf .bochs.cfg

libc:
	$(MAKE) -C libc

services: service
service: libc
	$(MAKE) -C service

kernel:
	$(MAKE) -C kernel

build/test.iso: all
	mkdir -p build/iso/boot/grub
	cp service/boot/boot.bin build/iso/boot/boot.bin
	cp kernel/kernel.bin build/iso/boot/kernel.bin
	cp .grub.cfg build/iso/boot/grub/grub.cfg
	grub-mkrescue -o build/test.iso build/iso

toolchain:
	mkdir -p build
	curl -o build/$(TOOLCHAIN).tar.xz http://newos.org/toolchains/$(TOOLCHAIN).tar.xz
	tar -C build/ -xvJpf build/$(TOOLCHAIN).tar.xz
	rm -f build/$(TOOLCHAIN).tar.xz

clean:
	$(MAKE) -C kernel clean
	$(MAKE) -C service clean
	$(MAKE) -C libc clean

veryclean: clean
	rm -Rf build

.PHONY: all clean kernel service test libc
