section .text
extern kmain
global start
start:
    cli
    jmp kmain
    hlt