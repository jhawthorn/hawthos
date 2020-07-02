#include "page_allocator.h"
#include "print.h"

/*
 * A trivial bump allocator.
 * This doesn't support freeing/reusing pages, it simply returns fresh pages
 * until it is out of memory.
 * Not intended to be a real allocator, just a stub until I decide how I to
 * actually handle this.
 */

#define MAX_SEGMENTS 8

struct memory_segment {
	uintptr_t start;
	uintptr_t length;
	uintptr_t current;
};

static struct memory_segment free_segments[MAX_SEGMENTS];
static int current_segment = MAX_SEGMENTS;

void init_page_allocator(multiboot_info_t *multiboot_info) {
	multiboot_memory_map_t *mmap = (multiboot_memory_map_t *) multiboot_info->mmap_addr;
	multiboot_memory_map_t *mmap_end = (multiboot_memory_map_t *) (multiboot_info->mmap_addr + multiboot_info->mmap_length);

	for (; mmap < mmap_end && current_segment != 0; mmap = (multiboot_memory_map_t *)((uintptr_t)mmap + mmap->size + 4)) {
		if (mmap->type == MULTIBOOT_MEMORY_AVAILABLE) {
			uint32_t addr = mmap->addr;
			uint32_t len = mmap->len;

			if (addr % PAGE_SIZE) {
				uint32_t diff = PAGE_SIZE - (addr % PAGE_SIZE);
				if (len <= diff)
					continue;
				addr += diff;
				len  -= diff;
			}

			if (len % PAGE_SIZE) {
				len -= len % PAGE_SIZE;
			}

			if (len == 0) {
				continue;
			}

			struct memory_segment *seg = &free_segments[--current_segment];
			seg->start = addr;
			seg->length = len;
			seg->current = addr + len;
		}
	}
}

uintptr_t page_alloc() {
	while (current_segment < MAX_SEGMENTS) {
		struct memory_segment *seg = &free_segments[current_segment];
		if ( seg->current != seg->start) {
			seg->current -= PAGE_SIZE;
			return seg->current;
		}

		/* Try next segment */
		current_segment++;
	}
	return 0;
}
