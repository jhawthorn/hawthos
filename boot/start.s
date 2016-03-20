.global _start
_start:
	mov $0xf00f00ab, %eax
	int $0x80
loop:
	jmp loop
