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

char *heap_end = &edata;

#define OS_PAGE_SIZE 4096

int brk(void *addr) {
	uintptr_t heap_page_end = ((uintptr_t)heap_end + OS_PAGE_SIZE - 1) / OS_PAGE_SIZE * OS_PAGE_SIZE;

	while ((uint32_t)addr > heap_page_end) {
		syscall(0x1001, heap_page_end, 0, 0, NULL);
		heap_page_end += 0x1000;
	}

	heap_end = addr;
	return 0;
}

void *sbrk(intptr_t increment) {
	uintptr_t base = (uintptr_t)heap_end;
	if (increment)
		brk((void *)(base + increment));
	return (void *)base;
}

void *memset(void *s, int c, size_t n) {
	char *ptr = s;
	while (n--) {
		*ptr++ = c;
	}
	return s;
}

int main() {
	/* Initialize bss section */
	brk(&end);
	memset(&edata, 0, (uintptr_t)&end - (uintptr_t)&edata);

	puts("hello, world\n");
	return 0;
}
