#ifndef GDT_H
#define GDT_H

#include <types.h>

struct gdt_segment_desc {
    u16 low_limit;
    u16 low_base;
    u8 mid_base;
    u8 access_byte;
    u8 high_limit : 4;
    u8 flags : 4;
    u8 high_base;
} __attribute__((packed));

struct gdt_descriptor {
    u16 size;
    u32 offset;
} __attribute__((packed));

extern struct gdt_descriptor gdt_desc;
extern void gdt_flush();

void gdt_set_gate(u32 index, u32 base, u32 limit, u8 access_byte, u8 flags);
void gdt_init();

#endif