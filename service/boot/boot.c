#include <stdint.h>
#include <stddef.h>

#include <stdio.h>

#include <hawthos.h>

int main() {
	printf("hello%c %s\n", ',', "world");

	uint32_t val = 0;
	ipc_recv(1, &val);
	printf("received: %i\n", val);
	return 0;
}
