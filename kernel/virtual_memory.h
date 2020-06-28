#define ADDRESS_TO_PAGE_NUMBER(addr) ((addr) >> 12)

#define PAGE_TABLE_OFFSET(addr) ((addr) >> 12)
#define PAGE_DIRECTORY_INDEX(addr) ((addr) >> 22)

#define KERNEL_VIRTUAL_BASE (0xC0000000)

#define PAGE_ENTRY(address, flags) \
	(((address) & 0xfffff000) | PAGE_PRESENT | flags)

#define PAGE_4MB          (1 << 7)
#define PAGE_USER         (1 << 2)
#define PAGE_WRITABLE     (1 << 1)
#define PAGE_PRESENT      (1 << 0)

void virtual_memory_init();
void virtual_memory_map(uint32_t virt, uint32_t phys, uint32_t flags);
void virtual_memory_unmap(uint32_t virt);
