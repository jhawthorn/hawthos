.global _start
_start:
	movl $stack_top, %esp
	push %eax

	mov $0x1001, %eax
	mov $0x1002, %ebx
	mov $0x1003, %ecx
	mov $0x1004, %edx
	int $0x80
loop:
	jmp loop

.section .data
.align 32
stack_bottom:
.skip 0x4000 # 16 KiB
stack_top:
