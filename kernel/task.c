#include <stdint.h>

#include "task.h"
#include "tss.h"
#include "print.h"
#include "virtual_memory.h"

task_t tasks[32];
int current_task_id = 0;
int total_tasks = 0;


void set_task(int task_id) {
   current_task_id = task_id;

   tss_set_esp0((uint32_t)tasks[task_id].stack_end);
   write_cr3(tasks[task_id].cr3);
}

int next_task_id() {
   return (current_task_id + 1) % total_tasks;
}

task_t *current_task() {
   return &tasks[current_task_id];
}

int create_task() {
   int task_id = total_tasks++;
   task_t *task = &tasks[task_id];

   task->task_id = task_id;
   task->state = 0;
   task->cr3 = virtual_memory_new_dir();

   task->stack.cs = 0x1B;
   task->stack.es = 0x23;
   task->stack.ss = 0x23;
   task->stack.ds = 0x23;
   task->stack.eip = 0x08000000;

   set_task(task_id);

   return task_id;
}

#define DUMP_REGISTER(name) \
   print(#name ": 0x"); \
   printnum(stack->name, 16); \
   print("\n");
void dump_task_registers(task_stack_t *stack) {
   DUMP_REGISTER(es)
   DUMP_REGISTER(ds)
   DUMP_REGISTER(edi)
   DUMP_REGISTER(esi)
   DUMP_REGISTER(ebp)
   DUMP_REGISTER(ebx)
   DUMP_REGISTER(edx)
   DUMP_REGISTER(ecx)
   DUMP_REGISTER(eax)
   DUMP_REGISTER(eip)
   DUMP_REGISTER(cs)
   DUMP_REGISTER(eflags)
   DUMP_REGISTER(esp)
   DUMP_REGISTER(ss)
}
#undef DUMP_REGISTER
