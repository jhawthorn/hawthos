# Based on http://wiki.osdev.org/Bare_bones

.set KERNEL_VIRTUAL_BASE, 0xC0000000
.set KERNEL_PAGE_NUMBER, (KERNEL_VIRTUAL_BASE >> 22)

# Declare constants used for creating a multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as in the Multiboot Standard. We put this into a special
# section so we can force the header to be in the start of the final program.
# You don't need to understand all these details as it is just magic values that
# is documented in the multiboot standard. The bootloader will search for this
# magic sequence and recognize us as a multiboot kernel.
.section .text
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.global _start
.type _start, @function
_start:
	movl $(boot_page_directory - KERNEL_VIRTUAL_BASE), %ecx
	movl %ecx, %cr3

	movl %cr4, %ecx
	or $0x00000010, %ecx
	movl %ecx, %cr4

	movl %cr0, %ecx
	or $0x80000000, %ecx
	movl %ecx, %cr0

	lea start_higher_half, %ecx
	jmp *%ecx

start_higher_half:

	# Pointer to the multiboot header structure arrives in ebx. We store
	# this before we accidentally clobber it.
	movl %ebx, multiboot_info

	# To set up a stack, we simply set the esp register to point to the top of
	# our stack (as it grows downwards).
	movl $stack_top, %esp

	# We are now ready to actually execute C code. We cannot embed that in an
	# assembly file, so we'll create a kernel.c file in a moment. In that file,
	# we'll create a C entry point called kernel_main and call it here.
	call kernel_main

	sti
.Lhang:
	hlt
	jmp .Lhang

# Set the size of the _start symbol to the current location '.' minus its start.
# This is useful when debugging or when you implement call tracing.
.size _start, . - _start

.section .data
.align 0x1000
boot_page_directory:
#.long 0x00000083
.long 0x00000085 # HAX: enable user permissions for now
.rept (KERNEL_PAGE_NUMBER - 1)
.long 0
.endr
.long 0x00000083
.rept (1024 - KERNEL_PAGE_NUMBER - 1)
.long 0
.endr

.section .bss
.align 32
stack_bottom:
.skip 0x1000 # 4 KiB
stack_top:
