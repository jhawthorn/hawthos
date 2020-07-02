#include <stdlib.h>
#include <string.h>

/* From linker script */
extern char etext, edata, end;

void pre_main() {
	/* Initialize bss section */
	brk(&end);
	memset(&edata, 0, (uintptr_t)&end - (uintptr_t)&edata);
}
