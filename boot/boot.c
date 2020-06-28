#include <stdint.h>

uint32_t syscall(uint32_t number, uint32_t arg1, uint32_t arg2, uint32_t arg3) {
	uint32_t ret;
    asm volatile ( "int $0x80" : "=a"(ret) : "a"(number), "b"(arg1), "c"(arg2), "d"(arg3) );
	return ret;
}

void putchar(char c) {
	syscall(0x1000, c, 0, 0);
}

void puts(char *s) {
	while (*s) {
		putchar(*s++);
	}
}

int main() {
	puts("hello, world\n");
	return 0;
}
