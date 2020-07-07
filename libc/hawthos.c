#include <hawthos.h>

void yield() {
	syscall(SYSCALL_YIELD, 0, 0, 0, 0);
}

int ipc_send(uint32_t task_id, uint32_t value) {
	return !!syscall(SYSCALL_IPC_SEND, task_id, value, 0, 0);
}

int ipc_recv(uint32_t task_id, uint32_t *value) {
	return !!syscall(SYSCALL_IPC_RECV, task_id, 0, 0, value);
}
