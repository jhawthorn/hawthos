#include "page_allocator.h"
#include "print.h"

void init_page_allocator(multiboot_info_t *multiboot_info) {
	multiboot_memory_map_t *mmap = (multiboot_memory_map_t *) multiboot_info->mmap_addr;
	multiboot_memory_map_t *mmap_end = (multiboot_memory_map_t *) (multiboot_info->mmap_addr + multiboot_info->mmap_length);

	while(mmap < mmap_end) {
		printnum(mmap->addr, 16);
		print(" - ");
		printnum(mmap->addr + mmap->len, 16);
		print(" : ");
		printnum(mmap->type, 10);
		print(" : ");
		printnum(mmap->size, 10);
		print("\n");

		mmap = (multiboot_memory_map_t *)((uintptr_t)mmap + mmap->size + 4);
	}
}
