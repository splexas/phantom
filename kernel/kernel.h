#ifndef KERNEL_H
#define KERNEL_H

void hlt()
{
    asm volatile("hlt");
}

#endif