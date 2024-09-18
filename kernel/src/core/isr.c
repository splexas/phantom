#include <kernel.h>
#include <core/isr.h>
#include <core/vga.h>

/*
When the CPU calls the interrupt handlers, the CPU pushes these values onto the stack in this order:

EFLAGS -> CS -> EIP

The CS value is padded with two bytes to form a doubleword.

If the gate type is not a trap gate, the CPU will clear the interrupt flag. If the interrupt is an exception, the CPU will push an error code onto the stack, as a doubleword.

The CPU will load the segment-selector value from the associated IDT descriptor into CS. 
*/

// http://wiki.osdev.org/Exceptions

void isr_handler()
{
    kprintf("got some interrupt\n");
}

void exception_handler()
{
    kprintf("got some exception\n");
    //CLI();
    //HLT();
}