#include <stdint.h>
#include <stddef.h>

int brk(void *addr);
void *sbrk(intptr_t increment);

void *malloc(size_t size);
void *calloc(size_t size, size_t nmemb);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
void exit(int status);
