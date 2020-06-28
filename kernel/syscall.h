uint32_t handle_syscall(uint32_t number, uint32_t arg1, uint32_t arg2, uint32_t arg3);

#define SYSCALL_FAILURE 0
#define SYSCALL_SUCCESS 1

#define SYSCALL_PRINT 0x1000
