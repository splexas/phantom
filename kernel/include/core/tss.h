#ifndef TSS_H
#define TSS_H

#include <types.h>

struct tss {
    u32 link; // previous tss segment selector
    u32 esp0;
    u32 ss0;
    u32 esp1;
    u32 ss1;
    u32 esp2;
    u32 ss2;
    u32 cr3;
    u32 eip;
    u32 eflags;
    u32 eax;
    u32 ecx;
    u32 edx;
    u32 ebx;
    u32 esp;
    u32 ebp;
    u32 esi;
    u32 edi;
    u32 es;
    u32 cs;
    u32 ss;
    u32 ds;
    u32 fs;
    u32 gs;
    u32 ldtr;
    u32 iopb;
    u32 ssp;
};

// defined in GDT file
extern struct tss tss;

void tss_load(u32 esp0);
void tss_init();

#endif