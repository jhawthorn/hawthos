#include <stdint.h>
#include <stddef.h>

#include <stdio.h>

#include <hawthos.h>

int main() {
	printf("hello%c %s\n", ',', "world");
	syscall(0x1002, 0, 0, 0, 0);
	return 0;
}
