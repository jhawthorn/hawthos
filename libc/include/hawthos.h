#include <stdint.h>

#define SYSCALL_SUCCESS 0
#define SYSCALL_FAILURE 1

#include "hawthos/syscall_constants.h"

uint32_t syscall(uint32_t number, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t *out);
void yield();

int ipc_send(uint32_t task_id, uint32_t value);
int ipc_recv(uint32_t task_id, uint32_t *value);

uint8_t io_inb(uint16_t port);
void io_outb(uint16_t port, uint8_t val);
uint16_t io_inw(uint16_t port);
void io_outw(uint16_t port, uint16_t val);
