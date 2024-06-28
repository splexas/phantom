#ifndef GDT_H
#define GDT_H

#include <types.h>

struct gdt_descriptor {
    u16 size;
    u32 offset;  
} __attribute__((packed));

struct gdt_entry {
    u16 limit_low;
    u16 base_low;
    u8 base_mid;
    u8 access;
    u8 limit_high : 4;
    u8 flags : 4;
    u8 base_high;
} __attribute__((packed));

void gdt_add_entry(u8 segment, u32 base, u32 limit, u8 access, u8 flags);
void gdt_install();

#endif