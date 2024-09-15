#include <kernel.h>

#include <grub/multiboot2.h>
#include <grub/mb2.h>

#include <types.h>
#include <core/vga.h>
#include <core/gdt.h>

#include <log.h>

__attribute__((noreturn)) void kmain(u32 mb2_addr, u32 mb2_magic)
{
    if (mb2_magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        log_err("Kernel wasn't booted by GRUB Multiboot2. Aborting.");
        goto terminate;
    }

    if (mb2_addr & 7) {
        log_err("Unaligned mbi: 0x%x. Aborting.", mb2_addr);
        goto terminate;
    }

    /* Parse necessary Multiboot2 data */
    struct mb2_info info;
    mb2_parse(mb2_addr, &info);

    if (!info.stack_ptr) {
        log_err("No suitable memory space was found for the stack. Aborting.");
        goto terminate;
    }

    log_debug("esp: %p\n", info.stack_ptr);
    SET_ESP(info.stack_ptr);

    /* Initialize GDT */
    gdt_init();
    log_ok("Loaded GDT!\n");

terminate:
    HLT();
    for (;;);
}
