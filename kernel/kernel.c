#include <vga.h>
#include <gdt.h>
#include <idt.h>

void kmain()
{
    kclear();
    gdt_install();
    klog("Entry", "GDT installed!");
    idt_install();
    klog("Entry", "IDT installed!");
    kdisplay_logo();
    kprint(VGA_WHITE, "test %s\n", "myarg");
    kprint(VGA_WHITE, "my num %d d\n", 12, 6969);
}
