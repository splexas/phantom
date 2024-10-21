[bits 32]
section .text

extern irq_handler

%macro irq_stub 1
irq_stub_%+%1:
    push %1
    call irq_handler
    add esp, 4
    iret
%endmacro

irq_stub 0
irq_stub 1
irq_stub 2
irq_stub 3
irq_stub 4
irq_stub 5
irq_stub 6
irq_stub 7
irq_stub 8
irq_stub 9
irq_stub 10
irq_stub 11
irq_stub 12
irq_stub 13
irq_stub 14
irq_stub 15

global irq_stub_table
irq_stub_table:
%assign i 0 
%rep    16
    dd irq_stub_%+i
%assign i i+1 
%endrep