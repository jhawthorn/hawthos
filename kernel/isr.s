.global resume_from_task_stack
resume_from_task_stack:
	mov 0x4(%esp), %esp
	pop %es
	pop %ds
	popa
	add $4, %esp
	iret

.macro define_isr num, error=0
.global isr\num
.align 16
isr\num:
.if \error == 0
push $0
.endif
pusha
cld
push %ds
push %es
mov $0x10, %cx
mov %cx, %ds
mov %cx, %es
mov %esp, %eax
movl $stack_top, %esp
push %eax
push $\num
call handle_interrupt
add $4, %esp
pop %esp
pop %es
pop %ds
popa
add $4, %esp
iret
.endm

define_isr 0
define_isr 1
define_isr 2
define_isr 3
define_isr 4
define_isr 5
define_isr 6
define_isr 7
define_isr 8, 1
define_isr 9
define_isr 10, 1
define_isr 11, 1
define_isr 12, 1
define_isr 13, 1
define_isr 14, 1
define_isr 15
define_isr 16
define_isr 17, 1
define_isr 18
define_isr 19
define_isr 20
define_isr 21
define_isr 22
define_isr 23
define_isr 24
define_isr 25
define_isr 26
define_isr 27
define_isr 28
define_isr 29
define_isr 30, 1
define_isr 31
define_isr 32
define_isr 33
define_isr 34
define_isr 35
define_isr 36
define_isr 37
define_isr 38
define_isr 39
define_isr 40
define_isr 41
define_isr 42
define_isr 43
define_isr 44
define_isr 45
define_isr 46
define_isr 47
define_isr 48
define_isr 49
define_isr 50
define_isr 51
define_isr 52
define_isr 53
define_isr 54
define_isr 55
define_isr 56
define_isr 57
define_isr 58
define_isr 59
define_isr 60
define_isr 61
define_isr 62
define_isr 63
define_isr 64
define_isr 65
define_isr 66
define_isr 67
define_isr 68
define_isr 69
define_isr 70
define_isr 71
define_isr 72
define_isr 73
define_isr 74
define_isr 75
define_isr 76
define_isr 77
define_isr 78
define_isr 79
define_isr 80
define_isr 81
define_isr 82
define_isr 83
define_isr 84
define_isr 85
define_isr 86
define_isr 87
define_isr 88
define_isr 89
define_isr 90
define_isr 91
define_isr 92
define_isr 93
define_isr 94
define_isr 95
define_isr 96
define_isr 97
define_isr 98
define_isr 99
define_isr 100
define_isr 101
define_isr 102
define_isr 103
define_isr 104
define_isr 105
define_isr 106
define_isr 107
define_isr 108
define_isr 109
define_isr 110
define_isr 111
define_isr 112
define_isr 113
define_isr 114
define_isr 115
define_isr 116
define_isr 117
define_isr 118
define_isr 119
define_isr 120
define_isr 121
define_isr 122
define_isr 123
define_isr 124
define_isr 125
define_isr 126
define_isr 127
define_isr 128

.global isr_addresses
isr_addresses:
.long isr0
.long isr1
.long isr2
.long isr3
.long isr4
.long isr5
.long isr6
.long isr7
.long isr8
.long isr9
.long isr10
.long isr11
.long isr12
.long isr13
.long isr14
.long isr15
.long isr16
.long isr17
.long isr18
.long isr19
.long isr20
.long isr21
.long isr22
.long isr23
.long isr24
.long isr25
.long isr26
.long isr27
.long isr28
.long isr29
.long isr30
.long isr31
.long isr32
.long isr33
.long isr34
.long isr35
.long isr36
.long isr37
.long isr38
.long isr39
.long isr40
.long isr41
.long isr42
.long isr43
.long isr44
.long isr45
.long isr46
.long isr47
.long isr48
.long isr49
.long isr50
.long isr51
.long isr52
.long isr53
.long isr54
.long isr55
.long isr56
.long isr57
.long isr58
.long isr59
.long isr60
.long isr61
.long isr62
.long isr63
.long isr64
.long isr65
.long isr66
.long isr67
.long isr68
.long isr69
.long isr70
.long isr71
.long isr72
.long isr73
.long isr74
.long isr75
.long isr76
.long isr77
.long isr78
.long isr79
.long isr80
.long isr81
.long isr82
.long isr83
.long isr84
.long isr85
.long isr86
.long isr87
.long isr88
.long isr89
.long isr90
.long isr91
.long isr92
.long isr93
.long isr94
.long isr95
.long isr96
.long isr97
.long isr98
.long isr99
.long isr100
.long isr101
.long isr102
.long isr103
.long isr104
.long isr105
.long isr106
.long isr107
.long isr108
.long isr109
.long isr110
.long isr111
.long isr112
.long isr113
.long isr114
.long isr115
.long isr116
.long isr117
.long isr118
.long isr119
.long isr120
.long isr121
.long isr122
.long isr123
.long isr124
.long isr125
.long isr126
.long isr127
.long isr128
