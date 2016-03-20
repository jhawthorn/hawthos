#include <stddef.h>
#include <stdint.h>

#include "print.h"

#define IDT_PRESENT 0x80
#define IDT_DPL(dpl) ((dpl) << 5)
#define IDT_GATE_INT32 0xe

#define KERNEL_CODE_SELECTOR 0x08

void generic_isr();

typedef struct __attribute__((packed)) {
   uint16_t offset_low;  /* offset bits 0..15 */
   uint16_t selector;    /* a code segment selector in GDT or LDT */
   uint8_t  _reserved;   /* unused, set to 0 */
   uint8_t  type;        /* type and attributes */
   uint16_t offset_high; /* offset bits 16..31 */
} interrupt_descriptor_t;

volatile interrupt_descriptor_t idt[129];

typedef struct __attribute__((__packed__)) {
	uint16_t size;
	uint32_t base;
} idtr_t;

idtr_t idtr = {
	.size = sizeof(idt),
	.base = (uint32_t) &idt[0]
};

void set_idt(size_t idx, uint32_t offset, uint8_t dpl) {
	idt[idx].offset_low = offset & 0xffff;
	idt[idx].offset_high = offset >> 16;
	idt[idx].selector = KERNEL_CODE_SELECTOR;
	idt[idx].type = IDT_PRESENT | IDT_GATE_INT32 | IDT_DPL(dpl);
}

extern uint32_t isr_addresses[0];

void load_idt() {
	for(int i = 0; i <= 127; i++) {
		set_idt(i, isr_addresses[i], 0);
	}

	/* int 0x80 is our system call interrupt */
	set_idt(128, isr_addresses[128], 3);

	asm ( "lidt %0" : : "m"(idtr) );
}
