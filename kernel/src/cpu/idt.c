#include <cpu/idt.h>

idtr_t idtr;
static idt_gate_t gates[256];

extern void *isr_stub_table[];

void idt_set_gate(uint8_t index, uint32_t offset, uint16_t selector,
                  uint8_t type, uint8_t dpl)
{
    gates[index].offset_low = offset & 0xffff;
    gates[index].seg_selector = selector;
    gates[index].type = type & 0xf;
    gates[index].zero = 0;
    gates[index].dpl = dpl & 0xf;
    gates[index].present = 1;
    gates[index].offset_high = offset >> 16;
}

void idt_init()
{
    for (uint8_t i = 0; i < 32; i++) {
        idt_set_gate(i, (uint32_t)isr_stub_table[i], 0x08, GATE_TYPE_32BIT_INT,
                     CPU_RING_0);
    }

    // todo: add irqs?
    idtr.size = sizeof(idt_gate_t) * 32 - 1;
    idtr.offset = (uint32_t)gates;
    idt_flush();
}