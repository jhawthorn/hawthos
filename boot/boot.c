#include <stdint.h>
#include <stddef.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* From linker script */
extern char etext, edata, end;

int main() {
	/* Initialize bss section */
	brk(&end);
	memset(&edata, 0, (uintptr_t)&end - (uintptr_t)&edata);

	puts("hello, world\n");
	return 0;
}
