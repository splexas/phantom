#ifndef _CPU_GDT_H
#define _CPU_GDT_H

#include <stdint.h>

typedef struct gdt_desc {
    uint16_t size;
    uint32_t offset;
} __attribute__((packed)) gdtr_t;

typedef struct gdt_segment_desc {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t limit_high : 4;
    uint8_t flags : 4;
    uint8_t base_high;
} __attribute__((packed)) gdt_segment_t;

extern gdtr_t gdtr;

void gdt_set_gate(uint8_t index, uint32_t base, uint32_t limit, uint8_t access,
                  uint8_t flags);
void gdt_init();
extern void gdt_flush();

#endif