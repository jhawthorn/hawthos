#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"
#include "print.h"
#include "pic.h"
#include "page_allocator.h"

void load_gdt();
void load_idt();

multiboot_info_t *multiboot_info;

void jump_usermode(uint32_t);

void kernel_main() {
	clear();
	print("Loaded HawthOS kernel\n");
	print("Version " VERSION "\n");
	print("\n");

	pic_init();
	load_gdt();
	load_idt();

	multiboot_module_t *mods = (multiboot_module_t *) multiboot_info->mods_addr;

	for(size_t i = 0; i < multiboot_info->mods_count; i++) {
		print((char *)mods[i].cmdline);
		print(":");
		printnum(mods[i].mod_start, 16);
		print(" - ");
		printnum(mods[i].mod_end, 16);
		print("\n");
	}

	init_page_allocator(multiboot_info);

	asm ("sti");
	if(multiboot_info->mods_count) {
		jump_usermode(mods[0].mod_start);
	} else {
		print("No modules specified.\n");
	}
}
