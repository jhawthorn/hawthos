#include <stdint.h>
#include <stddef.h>

#include <stdio.h>

#include <hawthos.h>

int main() {
	printf("hello%c %s\n", ',', "world");
	yield();
	printf("again\n");
	yield();
	return 0;
}
