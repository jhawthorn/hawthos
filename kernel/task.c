#include <stdint.h>

#include "task.h"
#include "tss.h"
#include "print.h"
#include "virtual_memory.h"

task_t tasks[32] __attribute__ ((aligned(64)));
int current_task_id = 0;
int total_tasks = 0;

void set_task(int task_id) {
   current_task_id = task_id;

   tss_set_esp0((uint32_t)tasks[task_id].stack_end);
   write_cr3(tasks[task_id].cr3);
}

task_t *current_task() {
   return &tasks[current_task_id];
}

task_t *get_task(int task_id) {
   if (task_id >= 0 && task_id < total_tasks) {
      return &tasks[task_id];
   } else {
      return 0;
   }
}

int create_task() {
   int task_id = total_tasks++;
   task_t *task = &tasks[task_id];

   task->task_id = task_id;
   task->state = TASK_RUNNING;
   task->cr3 = virtual_memory_new_dir();

   /* initialize stack */
   task->stack.cs = 0x1B;
   task->stack.ds = 0x23;
   task->stack.es = 0x23;
   task->stack.ss = 0x23;

   task->stack.eip = 0x08000000;

   task->stack.edi = 0;
   task->stack.esi = 0;
   task->stack.ebp = 0;
   task->stack.esp_discarded = 0;
   task->stack.ebx = 0;
   task->stack.edx = 0;
   task->stack.ecx = 0;
   task->stack.eax = 0;
   task->stack.eflags = 0;
   task->stack.esp = 0;

   task->stack.error_code = 0;

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

_Noreturn uint32_t resume_from_task_stack();

void return_to_task() {
   uint32_t esp = (uint32_t)&current_task()->stack;
   resume_from_task_stack(esp);
}

void switch_to_next_running_task() {
   int task_id = current_task_id;
   int previous_task = task_id;
   do {
      task_id = (task_id + 1) % total_tasks;
      if (tasks[task_id].state == TASK_RUNNING)
	 break;
   } while(task_id != previous_task);

   if (tasks[task_id].state != TASK_RUNNING) {
      print("ERROR: No remaining tasks to run\n");
      for(;;);
   }
   set_task(task_id);
}

void exit_current_task() {
   current_task()->state = TASK_EXITED;
   switch_to_next_running_task();
}
