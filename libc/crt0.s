
.macro syscall1 num, arg1
movl \num, %eax
movl \arg1, %ebx
int $0x80
.endm

.set STACK_TOP,  0xC0000000

.global _start
_start:
	# Allocate the last pages of userspace to use as the top of our stack
	syscall1 $0x1001, $(STACK_TOP - 0x1000)
	movl $(STACK_TOP), %esp

	call pre_main

	call main
loop:
	jmp loop
