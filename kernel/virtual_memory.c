#include "virtual_memory.h"
#include <stdint.h>

uint32_t boot_page_directory[1024] __attribute__ ((aligned(0x1000))) = {
   [0] = 0x00000085, /* FIXME: includes user permissions for now */
   [KERNEL_PAGE_NUMBER] = 0x00000083,
   [1023] = (uint32_t)&boot_page_directory[0]
};
