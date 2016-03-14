#include <stdint.h>

#include "io.h"
#include "print.h"
#include "pic.h"

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

void handle_interrupt(uint32_t interrupt) {
   if(interrupt < 0x20) {
   } else if (interrupt < 0x30) {
      handle_irq(interrupt - 0x20);
      return;
   }
   print("Received int 0x");
   printnum(interrupt, 16);
   print("\n");
}
