#include <stdint.h>

#include "page_allocator.h"
#include "print.h"
#include "syscall.h"
#include "virtual_memory.h"

uint32_t handle_syscall(uint32_t number, uint32_t arg1, uint32_t arg2, uint32_t arg3) {
   (void) arg2, (void) arg3;

   switch(number) {
      case SYSCALL_PRINT:
	 putchar(arg1 & 0xff);
	 return SYSCALL_SUCCESS;
      case SYSCALL_ALLOC_PAGE:
	 if ((arg1 & 0xfff) || arg1 >= KERNEL_VIRTUAL_BASE) {
	    print("ALLOC_PAGE failed\n");
	    return SYSCALL_FAILURE;
	 }

	 virtual_memory_map(arg1, page_alloc(), PAGE_WRITABLE | PAGE_USER);
	 return SYSCALL_SUCCESS;
   };

   return SYSCALL_FAILURE;
}
