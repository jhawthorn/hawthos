.global _start
_start:
	movl $stack_top, %esp

	call main
loop:
	jmp loop

.section .data
.align 32
stack_bottom:
.skip 0x4000 # 16 KiB
stack_top:
