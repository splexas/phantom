#ifndef TSS_H
#define TSS_H

#include "types.h"

struct tss {
    u8 link : 4;
    u8 esp0 : 4;
    u8 ss0 : 4;
    u8 esp1 : 4;
    u8 ss1 : 4;
    u8 esp2 : 4;
    u8 ss2 : 4;
    u8 cr3 : 4;
    u8 eip : 4;
    u8 eflags : 4;
    u8 eax : 4;
    u8 ecx : 4;
    u8 edx : 4;
    u8 ebx : 4;
    u8 esp : 4;
    u8 ebp : 4;
    u8 esi : 4;
    u8 edi : 4;
    u8 es : 4;
    u8 cs : 4;
    u8 ss : 4;
    u8 ds : 4;
    u8 fs : 4;
    u8 gs : 4;
    u8 ldtr : 4;
    u8 iopb : 4;
    u8 ssp : 4;
};

extern struct tss tss;

#endif