#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"
#include "print.h"
#include "pic.h"

void load_gdt();
void load_idt();

multiboot_info_t *multiboot_info;

void kernel_main() {
	clear();
	print("Loaded HawthOS kernel\n");
	print("Version " VERSION "\n");
	print("\n");

	print("Multiboot info:\n");
	print("mem_lower: ");
	printnum(multiboot_info->mem_lower, 10);
	print("\n");
	print("mem_upper: ");
	printnum(multiboot_info->mem_upper, 10);
	print("\n\n");

	pic_init();

	load_gdt();
	print("gdt loaded.\n");

	load_idt();
	print("idt loaded.\n");
}
