[bits 32]
section .text
extern kmain
global start
start:
    cli
    mov esp, stack_top

	push ebx
	push eax
    call kmain

section .bss
stack_bottom:
    resb 4096 * 16
stack_top: