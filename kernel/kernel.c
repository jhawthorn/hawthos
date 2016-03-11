#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

multiboot_info_t *multiboot_info;

volatile uint16_t *terminal_buffer = (uint16_t *)0xB8000;
size_t terminal_pos = 0;

void clear() {
	for (size_t y = 0; y < VGA_HEIGHT; y++)
		for (size_t x = 0; x < VGA_WIDTH; x++)
			terminal_buffer[y * VGA_WIDTH + x] = 0;
	terminal_pos = 0;
}

void putchar(char c) {
	if(terminal_pos < VGA_WIDTH * VGA_HEIGHT) {
		if(c == '\n') {
			terminal_pos += VGA_WIDTH - (terminal_pos % VGA_WIDTH);
		} else {
			terminal_buffer[terminal_pos++] = 0x0f00 | c;
		}
	}
}

void print(char *s) {
	while(*s) {
		putchar(*s++);
	}
}

void kernel_main() {
	clear();
	print("Loaded HawthOS kernel\n");
	print("Version " VERSION "\n");
	print("\n");
}
