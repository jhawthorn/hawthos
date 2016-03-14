.section .data

gdt:
# 0x00 Reserved
.long 0x00000000
.long 0x00000000
# 0x08 Code - ring 0
.long 0x0000FFFF
.long 0x00CF9A00
# 0x10 Data - ring 0
.long 0x0000FFFF
.long 0x00CF9200
# 0x18 Code - ring 3
.long 0x0000FFFF
.long 0x00CFFA00
# 0x20 Data - ring 3
.long 0x0000FFFF
.long 0x00CFF200
# 0x28 TSS
gdt_tss:
.long 0x00000068
.long 0x00008900
.size gdt, . - gdt

gdt_descriptor:
.short (. - gdt)/8
.long gdt

.section .text

.global load_gdt
load_gdt:
# We need to add the TSS's address to the tss segment
	mov $tss, %ecx
	shl $16, %ecx
	or %ecx, gdt_tss

	mov $tss, %eax
	mov $tss, %ecx
	shr $16, %ecx
	and $0x000000ff, %ecx
	and $0xff000000, %eax
	or %ecx, %eax
	or %eax, gdt_tss+4

# Load the GDT
	lgdt gdt_descriptor
	ljmp $0x08, $reload_cs
reload_cs:
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss

# Load TSS
	mov $0x2b, %ax
	ltr %ax

	ret
