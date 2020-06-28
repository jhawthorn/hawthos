CC=i686-elf-gcc
AS=i686-elf-as
ASFLAGS=
CPPFLAGS=
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
OBJECTS=start.o boot.o
TARGET=boot.bin

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
