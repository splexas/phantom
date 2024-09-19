#include <core/idt.h>
#include <core/isr.h>
#include <core/vga.h>

struct idt_descriptor idt_desc;
static struct idt_gate_desc idt_gates[256];

void idt_set_gate(u8 vec, u8 type, u8 dpl, u32 isr)
{
    idt_gates[vec].low_offset = isr & 0xffff;
    idt_gates[vec].segment_selector = 0x08;
    idt_gates[vec].gate_type = type;
    idt_gates[vec].dpl = dpl;
    idt_gates[vec].p = 1;
    idt_gates[vec].high_offset = (isr >> 16) & 0xffff;
}

void idt_init()
{
    // setup exceptions
    for (int i = 0; i < IDT_MAX_DESCRIPTORS; i++)
        idt_set_gate(i, IDT_32BIT_INTERRUPT_GATE, 0,
            (u32)isr_exception_table[i]);

    idt_desc.offset = (u32)idt_gates;
    idt_desc.size = sizeof(struct idt_gate_desc) * IDT_MAX_DESCRIPTORS - 1;
    idt_flush();
}