CC=cc
AS=as
ASFLAGS=--32
CFLAGS=-m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra
OBJECTS=boot.o kernel.o

all:
	$(AS) $(ASFLAGS) boot.s -o boot.o
	$(CC) -c kernel.c -o kernel.o $(CFLAGS)
	$(CC) -T linker.ld -o kernel.bin -ffreestanding -nostdlib $(CFLAGS) $(OBJECTS)
