#ifndef IDT_H
#define IDT_H

#include <types.h>

struct idt_descriptor {
    u16 size;
    u32 offset;
} __attribute__((packed));

struct idt_entry {
    u16 offset_low;
    u16 selector;
    u8 reserved;
    u8 type : 4;
    u8 zero : 1;
    u8 dpl : 2;
    u8 present : 1;
    u16 offset_high;
} __attribute__((packed));

struct interrupt_frame {
    u32 eax;
    u32 ecx;
    u32 edx;
    u32 ebx;
    u32 esp;           // Original ESP
    u32 ebp;
    u32 esi;
    u32 edi;
    u32 interrupt_number;
    u32 error_code;       // If not a errcode func, push 0 in macro
    u32 ip;
    u32 cs;
    u32 flags;
    u32 useresp;
    u32 ss;
} __attribute__((packed));

extern u32 isr_table[256];

extern void int_stub(); // asm routine
void isr_handle(struct interrupt_frame frame);
void idt_add_entry(u8 index, u16 selector, u32 offset, u8 type);
void idt_install();

#endif