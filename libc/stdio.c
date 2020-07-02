#include <stdio.h>

#include <stddef.h>

#include <hawthos.h>

int putchar(int c) {
	syscall(0x1000, c, 0, 0, NULL);
	return 0;
}

int puts(const char *s) {
	while (*s) {
		putchar(*s++);
	}
	return 0;
}
