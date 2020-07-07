CC=i686-elf-gcc
AS=i686-elf-as
ASFLAGS=
CPPFLAGS=

LIBCDIR=../../libc
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(LIBCDIR)/include
OBJECTS=boot.o
TARGET=boot.bin

all: $(TARGET)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

$(TARGET): $(OBJECTS) linker.ld $(LIBCDIR)/libc.a
	$(CC) -T linker.ld -o $(TARGET) -ffreestanding -nostdlib $(CFLAGS) $(OBJECTS) -L$(LIBCDIR) -l c

clean:
	$(RM) $(OBJECTS) $(TARGET)

.PHONY: all clean
