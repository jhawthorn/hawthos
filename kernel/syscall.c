#include "task.h"
#include "syscall.h"
#include "print.h"

int handle_syscall(task_stack_t *stack) {
   uint32_t syscall = stack->eax;
   switch(syscall) {
      case SYSCALL_PRINT:
	 putchar(stack->ebx & 0xff);
	 return 1;
   };
   return 0;
}
