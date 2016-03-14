#include <stdint.h>

#include "print.h"

void handle_interrupt(uint32_t interrupt) {
   print("Received int 0x");
   printnum(interrupt, 16);
   print("\n");
}
