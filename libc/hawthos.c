#include <hawthos.h>

void yield() {
	syscall(SYSCALL_YIELD, 0, 0, 0, 0);
}

int ipc_send_async(uint32_t task_id, uint32_t value) {
	return !!syscall(SYSCALL_IPC_SEND, task_id, value, 0, 0);
}

int ipc_send(uint32_t task_id, uint32_t value) {
	while (ipc_send_async(task_id, value)) {
		yield();
	}
	return 0;
}

int ipc_recv(uint32_t task_id, uint32_t *value) {
	return !!syscall(SYSCALL_IPC_RECV, task_id, 0, 0, value);
}

uint8_t io_inb(uint16_t port) {
	uint32_t ret;
	syscall(SYSCALL_INB, port, 0, 0, &ret);
	return ret;
}

void io_outb(uint16_t port, uint8_t val) {
	syscall(SYSCALL_OUTB, port, val, 0, 0);
}

uint16_t io_inw(uint16_t port) {
	uint32_t ret;
	syscall(SYSCALL_INW, port, 0, 0, &ret);
	return ret;
}

void io_outw(uint16_t port, uint16_t val) {
	syscall(SYSCALL_OUTW, port, val, 0, 0);
}

tid_t get_tid() {
	uint32_t ret;
	syscall(SYSCALL_GET_TID, 0, 0, 0, &ret);
	return ret;
}
