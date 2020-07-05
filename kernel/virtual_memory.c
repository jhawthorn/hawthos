#include <stdint.h>

#include "virtual_memory.h"
#include "page_allocator.h"
#include "print.h"

#define KERNEL_PAGE_DIRECTORY_INDEX PAGE_DIRECTORY_INDEX(KERNEL_VIRTUAL_BASE)

uint32_t boot_page_directory[1024] __attribute__ ((aligned(0x1000))) = {
   /* FIXME: includes user permissions for now */
   [0]                           = PAGE_ENTRY(0, PAGE_4MB | PAGE_WRITABLE),
   [KERNEL_PAGE_DIRECTORY_INDEX] = PAGE_ENTRY(0, PAGE_4MB | PAGE_WRITABLE),
};

#define PAGE_TABLE_MAPPING 0xFFC00000
#define PAGE_DIR_MAPPING 0xFFFFF000
#define PAGE_DIRECTORY_ENTRY(addr) (((uint32_t *)PAGE_DIR_MAPPING)[PAGE_DIRECTORY_INDEX(addr)])
#define PAGE_TABLE_ENTRY(addr) (((uint32_t *)PAGE_TABLE_MAPPING)[ADDRESS_TO_PAGE_NUMBER(addr)])
#define PAGE_TABLE_START(addr) PAGE_TABLE_ENTRY(addr & 0xFFC00000)

#define TEMP_PAGE_TABLE_MAPPING 0xFF800000
#define TEMP_PAGE_DIR_MAPPING 0xFFBFF000
#define TEMP_PAGE_DIRECTORY_ENTRY(addr) (((uint32_t *)TEMP_PAGE_DIR_MAPPING)[PAGE_DIRECTORY_INDEX(addr)])
#define TEMP_PAGE_TABLE_ENTRY(addr) (((uint32_t *)TEMP_PAGE_TABLE_MAPPING)[ADDRESS_TO_PAGE_NUMBER(addr)])
#define TEMP_PAGE_TABLE_START(addr) TEMP_PAGE_TABLE_ENTRY(addr & 0xFFC00000)

uint32_t read_cr3(void) {
    uint32_t val;
    asm volatile ( "mov %%cr3, %0" : "=r"(val) );
    return val;
}

void write_cr3(uint32_t val) {
    asm volatile ( "mov %0, %%cr3" : : "r"(val) );
}

static void reload_cr3() {
   write_cr3(read_cr3());
}

static inline void invlpg(uint32_t m) {
   asm volatile ( "invlpg (%0)" : : "b"(m) : "memory" );
}

void virtual_memory_init() {
   boot_page_directory[0] = 0;
   boot_page_directory[1023] = PAGE_ENTRY((uint32_t)&boot_page_directory[0] - KERNEL_VIRTUAL_BASE, PAGE_WRITABLE);
   reload_cr3();
}

void virtual_memory_map(uint32_t virt, uint32_t phys, uint32_t flags) {
	if (!(PAGE_DIRECTORY_ENTRY(virt) & PAGE_PRESENT)) {
		/* We need to set up a new page table for this location */
		PAGE_DIRECTORY_ENTRY(virt) = PAGE_ENTRY(page_alloc(), PAGE_WRITABLE | PAGE_USER);

		uint32_t *pt_cur = &PAGE_TABLE_START(virt);
		uint32_t *pt_end = pt_cur + 1024;
		invlpg((uint32_t)pt_cur);
		while (pt_cur != pt_end)
			*pt_cur++ = 0;
	} else if (PAGE_DIRECTORY_ENTRY(virt) & (PAGE_4MB)) {
		print("ERROR: tried to map on 4MB page\n");
		for(;;);
	}

	PAGE_TABLE_ENTRY(virt) = PAGE_ENTRY(phys, flags);
	invlpg(virt);
}

void virtual_memory_unmap(uint32_t virt) {
	if (!(PAGE_DIRECTORY_ENTRY(virt) & PAGE_PRESENT)) {
	   /* Nothing there */
	   return;
	}

	PAGE_TABLE_ENTRY(virt) = 0;
	invlpg(virt);
}

void virtual_memory_new_dir() {
	uint32_t *virt_page_dir = (uint32_t *)0xFFFFE000;
	uint32_t phys_page_dir = page_alloc();

	PAGE_DIRECTORY_ENTRY(TEMP_PAGE_TABLE_MAPPING) = PAGE_ENTRY(phys_page_dir, 0);
	invlpg((uint32_t)virt_page_dir);

	for(uint32_t i = 0; i < 1024; i++)
		virt_page_dir[i] = 0;

	virt_page_dir[KERNEL_PAGE_DIRECTORY_INDEX] = PAGE_ENTRY(0, PAGE_4MB | PAGE_WRITABLE);
	virt_page_dir[1023] = PAGE_ENTRY(phys_page_dir, PAGE_WRITABLE);

	PAGE_DIRECTORY_ENTRY(TEMP_PAGE_TABLE_MAPPING) = 0;
	invlpg((uint32_t)virt_page_dir);

	write_cr3(phys_page_dir);
}
