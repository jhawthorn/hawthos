#include <stdint.h>

#include "io.h"
#include "print.h"
#include "pic.h"
#include "task.h"
#include "tss.h"
#include "syscall.h"

#define BOCHS_BREAK asm volatile ( "xchgw %bx, %bx" )

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

#define INT_GENERAL_PROTECTION_FAULT 0xd
#define INT_PAGE_FAULT 0xe

void handle_interrupt(uint32_t interrupt) {
   task_stack_t *stack = &current_task()->stack;

   if(interrupt == INT_PAGE_FAULT) {
      uint32_t address;
      asm volatile ( "mov %%cr2, %0" : "=r"(address) );
      print("Page fault at: 0x");
      printnum(address, 16);
      print("\n");

      exit_current_task();
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
      uint32_t status = handle_syscall(stack->eax, stack->ebx, stack->ecx, stack->edx, &stack->ebx);
      stack->eax = status;
      return_to_task();
      return;
   }
   print("Received int 0x");
   printnum(interrupt, 16);
   print("\n");
}
