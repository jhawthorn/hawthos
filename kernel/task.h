#include "stdint.h"

typedef struct __attribute__((__packed__)) {
	/* push es */
	uint32_t es;

	/* push ds */
	uint32_t ds;

	/* pushad/popad */
	uint32_t edi;
	uint32_t esi;
	uint32_t ebp;
	uint32_t esp_discarded;
	uint32_t ebx;
	uint32_t edx;
	uint32_t ecx;
	uint32_t eax;

	uint32_t error_code;

	/* interrupt/iretd */
	uint32_t eip;
	uint32_t cs;
	uint32_t eflags;

	/* interrupt/iretd from lower rings */
	uint32_t esp;
	uint32_t ss;
} task_stack_t;

typedef struct {
	int task_id;
	int state;
	uint32_t cr3;
	task_stack_t stack __attribute__ ((aligned(64)));
	char stack_end[0];
} task_t;

/* Create a new task and switch to it */
int create_task();
task_t *current_task();
void set_task(int task_id);
void return_to_task();

void dump_task_registers(task_stack_t *stack);
