#include <stdint.h>

#define SYSCALL_SUCCESS 0
#define SYSCALL_FAILURE 1

#define SYSCALL_PRINT      0x1000
#define SYSCALL_ALLOC_PAGE 0x1001
#define SYSCALL_DUMP_REGS  0x1002
#define SYSCALL_YIELD      0x1003
#define SYSCALL_EXIT       0x1004

#define SYSCALL_IPC_SEND   0x1005
#define SYSCALL_IPC_RECV   0x1006

#define SYSCALL_INB        0x1010
#define SYSCALL_OUTB       0x1011
#define SYSCALL_INW        0x1012
#define SYSCALL_OUTW       0x1013

uint32_t syscall(uint32_t number, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t *out);
void yield();

int ipc_send(uint32_t task_id, uint32_t value);
int ipc_recv(uint32_t task_id, uint32_t *value);

uint8_t io_inb(uint16_t port);
void io_outb(uint16_t port, uint8_t val);
uint16_t io_inw(uint16_t port);
void io_outw(uint16_t port, uint16_t val);
