#include <stdint.h>

#include "io.h"
#include "print.h"
#include "pic.h"
#include "task.h"
#include "tss.h"
#include "syscall.h"

void handle_irq(uint32_t irq) {
   if (irq == 0) {
      /* timer */
   } else {
      print("Received IRQ 0x");
      printnum(irq, 16);
      print("\n");

   }
   pic_eoi(irq);
}

#define DUMP_REGISTER(name) \
   print(#name ": 0x"); \
   printnum(stack->name, 16); \
   print("\n");

static void dump_task_registers(task_stack_t *stack) {
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

#define INT_GENERAL_PROTECTION_FAULT 0xd
#define INT_PAGE_FAULT 0xe

void handle_interrupt(uint32_t interrupt, task_stack_t *stack) {
   if(interrupt == INT_PAGE_FAULT) {
      uint32_t address;
      asm volatile ( "mov %%cr2, %0" : "=r"(address) );
      print("Page fault at: 0x");
      printnum(address, 16);
      print("\n");
      return;
   } else if(interrupt == INT_GENERAL_PROTECTION_FAULT) {
      print("General protection fault in ");
      if(stack->ss & 2) {
	 print("IDT");
      } else if(stack->ss & 4) {
	 print("LDT");
      } else {
	 print("GDT");
      }
      print(" at index ");
      printnum((stack->ss >> 3) & 0x1f, 16);
      print("\n");
      asm volatile ( "hlt" );
      return;
   } else if(interrupt < 0x20) {
      print("Exception 0x");
      printnum(interrupt, 16);
      asm volatile ( "hlt" );
      return;
   } else if (interrupt < 0x30) {
      handle_irq(interrupt - 0x20);
      return;
   } else if (interrupt == 0x80) {
      uint32_t status = handle_syscall(stack->eax, stack->ebx, stack->ecx, stack->edx);
      stack->eax = status;
      return;
   }
   print("Received int 0x");
   printnum(interrupt, 16);
   print("\n");
}

#undef DUMP_REGISTER
