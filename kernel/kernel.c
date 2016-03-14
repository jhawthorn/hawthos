#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"
#include "print.h"
#include "pic.h"

void load_gdt();
void load_idt();

multiboot_info_t *multiboot_info;

void jump_usermode(uint32_t);

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
	load_idt();

	print("Going to boot things?\n");
	asm ("sti");
	if(multiboot_info->mods_count) {
		multiboot_module_t *mods = (multiboot_module_t *) multiboot_info->mods_addr;
		printnum(mods[0].mod_start, 16);
		print("\n");
		printnum(mods[0].mod_end, 16);
		print("\n");
		jump_usermode(mods[0].mod_start);
	} else {
		print("No modules specified.\n");
	}
}
