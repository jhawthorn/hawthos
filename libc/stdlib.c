#include <stdlib.h>

#include <hawthos.h>
#include <string.h>

/* From linker script */
extern char etext, edata, end;

static char *heap_end = &edata;

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

static size_t malloc_usable_size(void *ptr) {
	return *((uintptr_t *)ptr - 1);
}

void *malloc(size_t size) {
	uintptr_t *ptr = sbrk(size + sizeof(uintptr_t));
	*ptr = size;
	return (void *)(ptr + 1);
}

void *calloc(size_t size, size_t nmemb) {
	size_t total_size = size * nmemb;
	void *ptr = malloc(total_size);
	memset(ptr, 0, total_size);
	return ptr;
}

void free(void *ptr) {
	(void) ptr;
}

void *realloc(void *ptr, size_t size) {
	size_t old_size = malloc_usable_size(ptr);
	void *new_ptr = malloc(size);
	memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return new_ptr;
}
