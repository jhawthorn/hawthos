#include <stdint.h>

#include "multiboot.h"

void init_page_allocator(multiboot_info_t *multiboot_info);
uintptr_t page_alloc();

#define PAGE_SIZE 0x1000
