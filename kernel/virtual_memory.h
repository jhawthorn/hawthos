#define ADDRESS_TO_PAGE_NUMBER(addr) ((addr) >> 22)

#define KERNEL_VIRTUAL_BASE (0xC0000000)
#define KERNEL_PAGE_NUMBER (ADDRESS_TO_PAGE_NUMBER(KERNEL_VIRTUAL_BASE))