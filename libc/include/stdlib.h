#include <stdint.h>

int brk(void *addr);
void *sbrk(intptr_t increment);

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
void exit(int status);
