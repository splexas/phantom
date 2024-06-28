#include <gdt.h>
#include <vga.h>

// https://wiki.osdev.org/Global_Descriptor_Table

static struct gdt_entry gdt_entries[5];

void gdt_add_entry(u8 segment, u32 base, u32 limit, u8 access, u8 flags)
{
    gdt_entries[segment].base_low = base & 0xFFFF;
    gdt_entries[segment].base_mid = (base >> 16) & 0xFF;
    gdt_entries[segment].base_high = base >> 24;
    gdt_entries[segment].limit_low = limit & 0xFFFF;
    gdt_entries[segment].limit_high = (limit >> 16) & 0xF;
    gdt_entries[segment].flags = flags & 0xF; 
    gdt_entries[segment].access = access;
}

void gdt_install()
{
    struct gdt_descriptor desc;
    desc.offset = (u32)&gdt_entries;
    desc.size = sizeof(gdt_entries) - 1;
    gdt_add_entry(0, 0, 0, 0, 0);
    gdt_add_entry(1, 0, 0xFFFFF, 0x9A, 0xC); // kernel mode cs
    gdt_add_entry(2, 0, 0xFFFFF, 0x92, 0xC); // kernel mode ds
    gdt_add_entry(3, 0, 0xFFFFF, 0xFA, 0xC); // user mode cs
    gdt_add_entry(4, 0, 0xFFFFF, 0xF2, 0xC); // user mode ds
    asm volatile(
        "lgdt %0\n"
        "jmp $0x08,$reload_cs\n"
        "reload_cs:\n"
        "mov $0x10, %%ax\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        "mov %%ax, %%ss\n"
        :: "m"(desc)
    );
    return;
}