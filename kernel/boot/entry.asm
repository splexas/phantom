section .text
global start
extern kmain
start:
    cli 
    push eax ; multiboot2 magic value
    push ebx ; multiboot2 information
    call kmain