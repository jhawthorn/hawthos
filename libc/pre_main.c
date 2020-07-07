#include <stdlib.h>
#include <string.h>

/* From linker script */
extern char etext, edata, end;

/* Defined by user */
int main(int argc, char *argv[]);

void pre_main() {
	/* Initialize bss section */
	brk(&end);
	memset(&edata, 0, (uintptr_t)&end - (uintptr_t)&edata);

	int argc = 0;
	char *argv[] = {"", 0};

	int ret = main(argc, argv);

	exit(ret);
}
