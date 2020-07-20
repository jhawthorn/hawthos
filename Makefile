TOOLCHAIN=i686-elf-5.2.0-Linux-x86_64
export PATH := $(shell pwd)/build/$(TOOLCHAIN)/bin:$(PATH)

QEMUFLAGS=-display curses -serial mon:stdio -monitor telnet::45454,server,nowait

all: kernel services

build/qemu_args: services service/services.list
	{ \
		echo '-kernel kernel/kernel.bin'; \
		echo '-initrd service/boot/boot.bin,service/ping/ping.bin,service/keyboard/keyboard.bin,'; \
		echo -n '-initrd '; \
		for dir in $$(cat service/services.list); do \
			echo -n "service/$$dir/$$dir.bin,"; \
		done; \
		echo; \
	} > build/qemu_args

test: all build/qemu_args
	qemu-system-i386 $$(cat build/qemu_args) $(QEMUFLAGS)

test_qemu_debug: all build/qemu_args
	@echo in another terminal run: gdb
	qemu-system-i386 -S -s $$(cat build/qemu_args) $(QEMUFLAGS)

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
	for dir in $$(cat service/services.list); do cp "service/$$dir/$$dir.bin" build/iso/boot/; done
	cp kernel/kernel.bin build/iso/boot/kernel.bin
	{ \
		echo 'set timeout=0'; \
		echo 'set default=0'; \
		echo 'menuentry "HawthOS" {'; \
		echo 'multiboot /boot/kernel.bin'; \
		for dir in $$(cat service/services.list); do \
			echo "module /boot/$$dir.bin"; \
		done; \
		echo '}'; \
	} > build/iso/boot/grub/grub.cfg
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
