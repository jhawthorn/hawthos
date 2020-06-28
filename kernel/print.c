#include <stddef.h>
#include <stdint.h>

#include "print.h"
#include "io.h"

static volatile uint16_t *terminal_buffer = (uint16_t *)0xC00B8000;
static size_t terminal_pos = 0;

static void update_cursor() {
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (terminal_pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((terminal_pos >> 8) & 0xFF));
}

void clear() {
	for (size_t y = 0; y < VGA_HEIGHT; y++)
		for (size_t x = 0; x < VGA_WIDTH; x++)
			terminal_buffer[y * VGA_WIDTH + x] = 0;
	terminal_pos = 0;
}

static void putchar_s(char c) {
	if(c == '\n') {
		do {
			putchar(' ');
		} while(terminal_pos % VGA_WIDTH);
	} else {
		terminal_buffer[terminal_pos++] = 0x0f00 | c;
		if (terminal_pos == VGA_WIDTH * VGA_HEIGHT) {
			for (int i = 0; i < VGA_WIDTH * (VGA_HEIGHT - 1); i++) {
				terminal_buffer[i] = terminal_buffer[i + VGA_WIDTH];
			}
			for (int i = VGA_WIDTH * (VGA_HEIGHT - 1); i < VGA_WIDTH * VGA_HEIGHT; i++) {
				terminal_buffer[i] = 0;
			}
			terminal_pos = VGA_WIDTH * (VGA_HEIGHT - 1);
		}
	}
}

void putchar(char c) {
	putchar_s(c);
	update_cursor();
}

void print(char *s) {
	while(*s) {
		putchar_s(*s++);
	}
	update_cursor();
}

void printnum(uint32_t num, uint32_t radix) {
	if(num >= radix) {
		printnum(num / radix, radix);
	}
	num %= radix;
	if (num >= 10) {
		putchar_s('A' + (num - 10));
	} else {
		putchar_s('0' + num);
	}
	update_cursor();
}
