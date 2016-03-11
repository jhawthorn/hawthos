#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

volatile uint16_t *terminal_buffer = (uint16_t *)0xB8000;
size_t terminal_pos = 0;

void clear() {
	for (size_t y = 0; y < VGA_HEIGHT; y++)
		for (size_t x = 0; x < VGA_WIDTH; x++)
			terminal_buffer[y * VGA_WIDTH + x] = 0;
	terminal_pos = 0;
}

void puts(char *s) {
	while(*s && terminal_pos < VGA_WIDTH * VGA_HEIGHT) {
		terminal_buffer[terminal_pos++] = 0x0f00 | *s++;
	}
	terminal_pos += VGA_WIDTH - (terminal_pos % VGA_WIDTH);
}

void kernel_main() {
	clear();
	puts("Loaded HawthOS kernel");
	puts("Version " VERSION);
}
