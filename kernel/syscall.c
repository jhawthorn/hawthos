#include <stdint.h>

#include "page_allocator.h"
#include "print.h"
#include "syscall.h"
#include "task.h"
#include "virtual_memory.h"
#include "io.h"

#include "../libc/include/hawthos/syscall_constants.h"

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
	 switch_to_next_running_task();
	 return SYSCALL_SUCCESS;
      case SYSCALL_EXIT:
	 exit_current_task();
	 return SYSCALL_SUCCESS;
      case SYSCALL_IPC_SEND:
	 {
	    task_t *target = get_task(arg1);
	    if (target && target->state == TASK_IPC_RECV) {
	       target->stack.ebx = arg2;
	       set_task(target->task_id);
	       return SYSCALL_SUCCESS;
	    } else {
	       return SYSCALL_FAILURE;
	    }
	 }
      case SYSCALL_IPC_RECV:
	 current_task()->state = TASK_IPC_RECV;
	 switch_to_next_running_task();
	 return SYSCALL_SUCCESS;
      case SYSCALL_INB:
	 *ret = inb(arg1);
	 return SYSCALL_SUCCESS;
      case SYSCALL_OUTB:
	 outb(arg1, arg2);
	 return SYSCALL_SUCCESS;
      case SYSCALL_INW:
	 *ret = inw(arg1);
	 return SYSCALL_SUCCESS;
      case SYSCALL_OUTW:
	 outw(arg1, arg2);
	 return SYSCALL_SUCCESS;
      default:
	 print("Unknown syscall\n");
	 return SYSCALL_FAILURE;
   };

   return SYSCALL_FAILURE;
}
