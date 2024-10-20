#ifndef _CPU_IDT_H
#define _CPU_IDT_H

#include <stdint.h>

#define CPU_RING_0 0x0
#define CPU_RING_1 0x1
#define CPU_RING_2 0x2
#define CPU_RING_3 0x3

#define GATE_TYPE_TASK 0x5
#define GATE_TYPE_16BIT_INT 0x6
#define GATE_TYPE_16BIT_TRAP 0x7
#define GATE_TYPE_32BIT_INT 0xE
#define GATE_TYPE_32BIT_TRAP 0xF

typedef struct idt_desc {
    uint16_t size;
    uint32_t offset;
} __attribute__((packed)) idtr_t;

typedef struct idt_gate_desc {
    uint16_t offset_low;
    uint16_t seg_selector;
    uint8_t reserved;
    uint8_t type : 4;
    uint8_t zero : 1;
    uint8_t dpl : 2; // cpu privilege level
    uint8_t present : 1;
    uint16_t offset_high;
} __attribute__((packed)) idt_gate_t;

extern idtr_t idtr;

void idt_set_gate(uint8_t index, uint32_t offset, uint16_t selector,
                  uint8_t type, uint8_t dpl);
void idt_init();
extern void idt_flush();

#endif