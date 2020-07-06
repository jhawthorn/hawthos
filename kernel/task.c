#include <stdint.h>

#include "task.h"
#include "tss.h"
#include "virtual_memory.h"

typedef struct {
   int state;
   uint32_t cr3;
   char stack[4096] __attribute__ ((aligned(64)));
   char stack_end[0];
} task_t;

task_t tasks[32];
int current_task = 0;
int total_tasks = 0;


void set_task(int task_id) {
   current_task = task_id;

   tss_set_esp0((uint32_t)tasks[task_id].stack_end);
   write_cr3(tasks[task_id].cr3);
}

int create_task() {
   int task_id = total_tasks++;

   tasks[task_id].state = 0;
   tasks[task_id].cr3 = virtual_memory_new_dir();

   set_task(task_id);

   return task_id;
}
