#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"
#include "print.h"
#include "pic.h"
#include "page_allocator.h"
#include "virtual_memory.h"

void load_gdt();
void load_idt();

/* Address set from start.s */
uint32_t multiboot_info_addr;

void jump_usermode(uint32_t);

#define USER_VIRT_ADDRESS 0x08000000

#define BOCHS_BREAK asm volatile ( "xchgw %bx, %bx" )

void kernel_main() {
	clear();
	print("Loaded HawthOS kernel\n");
	print("Version " VERSION "\n");
	print("\n");

	pic_init();
	load_gdt();
	load_idt();

	multiboot_info_t *multiboot_info = (multiboot_info_t *)(multiboot_info_addr + KERNEL_VIRTUAL_BASE);

	init_page_allocator(multiboot_info);
	virtual_memory_init();

	multiboot_module_t *mods = (multiboot_module_t *)(multiboot_info->mods_addr + KERNEL_VIRTUAL_BASE);
	if (multiboot_info->mods_count == 0) {
		print("No modules specified.\n");
		return;
	}

	for(size_t i = 0; i < multiboot_info->mods_count; i++) {
		uint32_t mod_start = mods[i].mod_start;
		uint32_t mod_end   = mods[i].mod_end;

		print((char *)(mods[i].cmdline + KERNEL_VIRTUAL_BASE));
		print(":");
		printnum(mod_start, 16);
		print(" - ");
		printnum(mod_end, 16);
		print("\n");

		int task_id = create_task();
		set_task(task_id);
		for (uint32_t page = 0; page < mod_end - mod_start; page += 0x1000) {
			virtual_memory_map(USER_VIRT_ADDRESS+page, mod_start+page, PAGE_WRITABLE | PAGE_USER);
		}
	}

	set_task(0);

	asm ("sti");
	jump_usermode(USER_VIRT_ADDRESS);
}
