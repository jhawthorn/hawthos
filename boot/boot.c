#include <stdint.h>
#include <stddef.h>

uint32_t syscall(uint32_t number, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t *out) {
	uint32_t status;
	uint32_t ret;
	asm volatile ( "int $0x80" : "=a"(status), "=b"(ret) : "a"(number), "b"(arg1), "c"(arg2), "d"(arg3) );
	if (out)
		*out = ret;
	return status;
}

void putchar(char c) {
	syscall(0x1000, c, 0, 0, NULL);
}

void puts(char *s) {
	while (*s) {
		putchar(*s++);
	}
}

/* From linker script */
extern char etext, edata, end;

int main() {
	/* Initialize bss section */
	for (uintptr_t page = (uintptr_t)&edata; page < (uintptr_t)&end; page += 0x1000) {
		syscall(0x1001, page, 0, 0, NULL);
	}
	for (char *ptr = &edata; ptr < &end; ptr++) {
		*ptr = 0;
	}

	puts("hello, world\n");
	return 0;
}
