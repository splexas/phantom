#include <cpu/gdt.h>

gdtr_t gdtr;
static gdt_segment_t gdt_segments[5];

void gdt_set_gate(uint8_t index, uint32_t base, uint32_t limit, uint8_t access,
                  uint8_t flags)
{
    gdt_segments[index].limit_low = limit & 0xffff;
    gdt_segments[index].base_low = base & 0xffff;
    gdt_segments[index].base_mid = (base >> 16) & 0xff;
    gdt_segments[index].access = access;
    gdt_segments[index].limit_high = (limit >> 16) & 0xf;
    gdt_segments[index].flags = flags & 0xf;
    gdt_segments[index].base_high = base >> 24;
}

void gdt_init()
{
    gdt_set_gate(0, 0, 0, 0, 0);

    // kernel mode code segment
    gdt_set_gate(1, 0, 0xfffff, 0x9a, 0xc);
    // kernel mode data segment
    gdt_set_gate(2, 0, 0xfffff, 0x92, 0xc);
    // user mode code segment
    gdt_set_gate(3, 0, 0xfffff, 0xfa, 0xc);
    // user mode data segment
    gdt_set_gate(4, 0, 0xfffff, 0xf2, 0xc);

    gdtr.size = sizeof(gdt_segments) - 1;
    gdtr.offset = (uint32_t)gdt_segments;
    gdt_flush();
}