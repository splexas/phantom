#include "../include/gdt.h"
#include "../include/tss.h"

struct gdt_descriptor gdt_desc;

static struct gdt_segment_desc gdt_entries[5];

void gdt_set_gate(u32 index, u32 base, u32 limit, u8 access_byte, u8 flags)
{
    gdt_entries[index].low_limit = limit & 0xffff;
    gdt_entries[index].low_base = base & 0xffff;
    gdt_entries[index].mid_base = (base >> 16) & 0xff;
    gdt_entries[index].access_byte = access_byte;
    gdt_entries[index].high_limit = (limit >> 16) & 0xf;
    gdt_entries[index].flags = flags & 0xf;
    gdt_entries[index].high_base = (base >> 24) & 0xff;
}

void gdt_init()
{
    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0, 0xfffff, 0x9a, 0xc);
    gdt_set_gate(2, 0, 0xfffff, 0x92, 0xc);
    gdt_set_gate(3, 0, 0xfffff, 0xfa, 0xc);
    gdt_set_gate(4, 0, 0xfffff, 0xf2, 0xc);
    //gdt_set_gate(5, (u32)&tss, sizeof(tss) - 1, 0x89, 0);

    gdt_desc.size = sizeof(gdt_entries) - 1;
    gdt_desc.offset = (u32)gdt_entries;
    gdt_flush();
}
