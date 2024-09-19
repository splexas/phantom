#ifndef IDT_H
#define IDT_H

#include <types.h>

#define IDT_MAX_DESCRIPTORS 32

#define IDT_TASK_GATE 0x05
#define IDT_16BIT_INTERRUPT_GATE 0x6
#define IDT_16BIT_TRAP_GATE 0x07
#define IDT_32BIT_INTERRUPT_GATE 0xE
#define IDT_32BIT_TRAP_GATE 0xF

struct idt_descriptor {
    u16 size;
    u32 offset;
} __attribute__((packed));

struct idt_gate_desc {
    u16 low_offset;
    u16 segment_selector;
    u8 reserved;
    u8 gate_type : 4;
    u8 zero : 1;
    u8 dpl : 2;
    u8 p : 1;
    u16 high_offset;
} __attribute__((packed));

extern struct idt_descriptor idt_desc;
extern void *isr_exception_table[];

extern void idt_flush();

void idt_set_gate(u8 vec, u8 type, u8 dpl, u32 isr);
void idt_init();

#endif