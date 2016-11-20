.section .data

# Segment Format:

# 31           24                                 7             0
#+---------------+-------+-------+---------------+---------------+
#| Base (24-31)  | Flags |Limit' | Type          | Base (16-23)  |
#+---------------+-------+-------+---------------+---------------+
#+-------------------------------+-------------------------------+
#| Base (0-15)                   | Limit (0-15)                  |
#+-------------------------------+-------------------------------+
#

gdt:
# 0x00 Reserved "null" descriptor
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
# 0x28 TSS (with address unset)
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
# The TSS segment needs to hold the address, but the way it is specified is too
# awkward to do at link time.
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
# The GDT is now loaded, but for it to take effect, we need to reload the
# segment registers.

# ljmp into our new ring 0 code segment
	ljmp $0x08, $reload_cs
reload_cs:

# Set all data selectors to the new ring 0 data segment
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss

# Load the TSS via its descriptor in the gdt
	mov $0x2b, %ax
	ltr %ax

	ret
