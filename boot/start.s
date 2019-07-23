.global _start
_start:
	mov $0x1001, %eax
	mov $0x1002, %ebx
	mov $0x1003, %ecx
	mov $0x1004, %edx
	int $0x80
loop:
	hlt
	jmp loop
