#include <stdint.h>

#include "syscall.h"
#include "print.h"

uint32_t handle_syscall(uint32_t number, uint32_t arg1, uint32_t arg2, uint32_t arg3) {
   (void) arg2, (void) arg3;

   switch(number) {
      case SYSCALL_PRINT:
	 putchar(arg1 & 0xff);
	 return SYSCALL_SUCCESS;
   };

   return SYSCALL_FAILURE;
}
