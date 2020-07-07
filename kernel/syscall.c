#include <stdint.h>

#include "page_allocator.h"
#include "print.h"
#include "syscall.h"
#include "task.h"
#include "virtual_memory.h"

uint32_t handle_syscall(uint32_t number, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t *ret) {
   (void) arg2, (void) arg3, (void) ret;

   switch(number) {
      case SYSCALL_PRINT:
	 putchar(arg1 & 0xff);
	 return SYSCALL_SUCCESS;
      case SYSCALL_ALLOC_PAGE:
	 if (arg1 & 0xfff) {
	    print("ALLOC_PAGE failed: not aligned\n");
	    return SYSCALL_FAILURE;
	 }
	 if (arg1 >= KERNEL_VIRTUAL_BASE) {
	    print("ALLOC_PAGE failed: in kernel space\n");
	    return SYSCALL_FAILURE;
	 }

	 virtual_memory_map(arg1, page_alloc(), PAGE_WRITABLE | PAGE_USER);
	 return SYSCALL_SUCCESS;
      case SYSCALL_DUMP_REGS:
	 dump_task_registers(&current_task()->stack);
	 return SYSCALL_SUCCESS;
      case SYSCALL_YIELD:
	 set_task(next_task_id());
	 return_to_task();
	 return SYSCALL_SUCCESS;
      case SYSCALL_EXIT:
	 return SYSCALL_SUCCESS;
      default:
	 print("Unknown syscall\n");
	 return SYSCALL_FAILURE;
   };

   return SYSCALL_FAILURE;
}
