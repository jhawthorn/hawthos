CC=i686-elf-gcc
AS=i686-elf-as
ASFLAGS=
CPPFLAGS=

COMMONDIR=../common
LIBCDIR=../../libc
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(LIBCDIR)/include
TARGET=$(SERVICE).bin
LINKERFILE=$(COMMONDIR)/linker.ld

all: $(TARGET)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS) $(LINKERFILE) $(LIBCDIR)/libc.a
	$(CC) -T $(LINKERFILE) -o $(TARGET) -ffreestanding -nostdlib $(CFLAGS) $(OBJECTS) -L$(LIBCDIR) -l c

clean:
	$(RM) $(OBJECTS) $(TARGET)

.PHONY: all clean
