CC=i686-elf-gcc
AS=i686-elf-as
ASFLAGS=
CPPFLAGS=-DVERSION=\"0.1\"
CFLAGS=-std=gnu99 -ffreestanding -mno-mmx -mno-sse -mno-sse2 -O2 -Wall -Wextra
OBJECTS=start.o kernel.o print.o gdt.o tss.o idt.o isr.o interrupt.o pic.o page_allocator.o virtual_memory.o syscall.o task.o
TARGET=kernel.bin

all: $(TARGET)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

$(TARGET): $(OBJECTS) linker.ld
	$(CC) -T linker.ld -o $(TARGET) -ffreestanding -nostdlib $(CFLAGS) $(OBJECTS)

clean:
	$(RM) $(OBJECTS) $(TARGET)

.PHONY: all clean
