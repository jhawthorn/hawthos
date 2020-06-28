.global _start
_start:
	movl $stack_top, %esp
	push %eax

	mov $0x1000, %eax
	mov $'h', %ebx
	int $0x80
	mov $0x1000, %eax
	mov $'e', %ebx
	int $0x80
	mov $0x1000, %eax
	mov $'l', %ebx
	int $0x80
	mov $0x1000, %eax
	mov $'l', %ebx
	int $0x80
	mov $0x1000, %eax
	mov $'o', %ebx
	int $0x80
loop:
	jmp loop

.section .data
.align 32
stack_bottom:
.skip 0x4000 # 16 KiB
stack_top:
