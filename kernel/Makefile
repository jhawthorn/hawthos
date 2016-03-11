CC=cc
AS=as
ASFLAGS=--32
CPPFLAGS=
CFLAGS=-m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra
OBJECTS=boot.o kernel.o
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
