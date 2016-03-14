.global jump_usermode
jump_usermode:
	mov $0x23, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs # we don't need to worry about SS. it's handled by iret

	mov 0x4(%esp), %ecx # move eip argument into ecx
	mov %esp, %eax
	push $0x23 # user data segment with bottom 2 bits set for ring 3
	push %eax # push our current stack just for the heck of it
	pushf
	push $0x1B # user code segment with bottom 2 bits set for ring 3
	push %ecx
	iret
