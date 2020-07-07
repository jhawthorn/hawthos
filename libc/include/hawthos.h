#include <stdint.h>

#define SYSCALL_SUCCESS 0
#define SYSCALL_FAILURE 1

#define SYSCALL_PRINT      0x1000
#define SYSCALL_ALLOC_PAGE 0x1001
#define SYSCALL_DUMP_REGS  0x1002
#define SYSCALL_YIELD      0x1003

uint32_t syscall(uint32_t number, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t *out);
void yield();
