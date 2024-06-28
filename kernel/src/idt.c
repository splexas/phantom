#include <idt.h>
#include <vga.h>

// https://wiki.osdev.org/Interrupt_Descriptor_Table

static struct idt_entry idt_entries[256];
static const char* exceptions[] = {
    "Division By Zero",
    "Debug",
    "Nonmaskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 FPU Error"
    "Alignment Check",
    "Machine Check",
    "Simd Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    "Reserved"
};

void isr_handle(struct interrupt_frame frame)
{
    if (frame.interrupt_number <= 0x1F) {
        kprint(VGA_WHITE, "An exception has occured. %s\n", exceptions[frame.interrupt_number]);
        asm volatile ("cli");
        for (;;) asm volatile ("hlt");
    }
    kprint(VGA_WHITE, "Other interrupt has arrived.\n");
}

void idt_add_entry(u8 index, u16 selector, u32 offset, u8 type)
{
    idt_entries[index].offset_low = offset & 0xFFFF;
    idt_entries[index].offset_high = offset >> 16;
    idt_entries[index].selector = selector;
    idt_entries[index].reserved = 0;
    idt_entries[index].type = type & 0xF;
    idt_entries[index].zero = 0;
    idt_entries[index].dpl = 0; // ring 0
    idt_entries[index].present = 1;
}

void idt_install()
{
    struct idt_descriptor desc;
    desc.offset = (u32)&idt_entries;
    desc.size = sizeof(idt_entries) - 1;
    for (int i = 0; i < 256; i++)
        idt_add_entry(i, 0x08, isr_table[i], 14);
    asm volatile (
        "lidt %0\n"
        "sti"
        :: "m"(desc)
    );
}
