CC=i686-elf-gcc
AS=i686-elf-as
ASFLAGS=
CPPFLAGS=-DVERSION=\"0.1\"
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
OBJECTS=boot.o kernel.o print.o gdt.o tss.o idt.o isr.o interrupt.o pic.o
TARGET=kernel.bin

all: $(TARGET)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

$(TARGET): $(OBJECTS) linker.ld
	$(CC) -T linker.ld -o kernel.bin -ffreestanding -nostdlib $(CFLAGS) $(OBJECTS)

clean:
	$(RM) $(OBJECTS) $(TARGET)

.PHONY: all clean
