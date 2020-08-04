CC=i686-elf-gcc
AS=i686-elf-as
ASFLAGS=
CPPFLAGS=-Iinclude
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
OBJECTS=crt0.o pre_main.o syscall.o stdlib.o stdio.o string.o hawthos.o

all: libc.a

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(CC) $(CPPFLAGS) $(ASFLAGS) -c -o $@ $<

libc.a: $(OBJECTS)
	ar -rcs $@ $(OBJECTS)

clean:
	$(RM) $(OBJECTS) libc.a

.PHONY: all clean
