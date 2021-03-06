#include <hawthos/syscall_constants.h>

.macro syscall1 num, arg1
movl \num, %eax
movl \arg1, %ebx
int $0x80
.endm

.set STACK_TOP,  0xC0000000

.global _start
_start:
	/* Allocate the last pages of userspace to use as the top of our stack */
	syscall1 $SYSCALL_ALLOC_PAGE, $(STACK_TOP - 0x1000)
	syscall1 $SYSCALL_ALLOC_PAGE, $(STACK_TOP - 0x2000)
	syscall1 $SYSCALL_ALLOC_PAGE, $(STACK_TOP - 0x3000)
	syscall1 $SYSCALL_ALLOC_PAGE, $(STACK_TOP - 0x4000)
	movl $(STACK_TOP), %esp

	call pre_main
loop:
	jmp loop
