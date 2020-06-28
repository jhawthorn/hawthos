#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"
#include "print.h"
#include "pic.h"
#include "page_allocator.h"
#include "virtual_memory.h"

void load_gdt();
void load_idt();

multiboot_info_t *multiboot_info;

void jump_usermode(uint32_t);

#define BOCHS_BREAK asm volatile ( "xchgw %bx, %bx" )

void kernel_main() {
	clear();
	print("Loaded HawthOS kernel\n");
	print("Version " VERSION "\n");
	print("\n");

	pic_init();
	load_gdt();
	load_idt();

	multiboot_module_t *mods = (multiboot_module_t *)(multiboot_info->mods_addr + KERNEL_VIRTUAL_BASE);
	if (multiboot_info->mods_count == 0) {
		print("No modules specified.\n");
		return;
	}

	for(size_t i = 0; i < multiboot_info->mods_count; i++) {
		print((char *)mods[i].cmdline);
		print(":");
		printnum(mods[i].mod_start, 16);
		print(" - ");
		printnum(mods[i].mod_end, 16);
		print("\n");
	}
	uint32_t boot_mod_start = mods[0].mod_start;

	init_page_allocator(multiboot_info);
	virtual_memory_init();

	virtual_memory_map(boot_mod_start, boot_mod_start, PAGE_WRITABLE | PAGE_USER);

	asm ("sti");
	jump_usermode(boot_mod_start);
}
