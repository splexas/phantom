#include "kernel.h"

#include "include/multiboot2.h"
#include "include/mb2.h"

#include "include/types.h"
#include "include/vga.h"
#include "include/gdt.h"

#include "include/log.h"

__attribute__((noreturn)) void kmain(u32 mb2_boot_addr, u32 mb2_magic)
{
    if (mb2_magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        log_err("Kernel wasn't booted by GRUB Multiboot2. Aborting.");
        goto terminate;
    }

    if (mb2_boot_addr & 7) {
        log_err("Unaligned mbi: 0x%x. Aborting.", mb2_boot_addr);
        goto terminate;
    }

    /* Parse necessary Multiboot2 data */
    struct mb2_info info;
    mb2_parse(mb2_boot_addr, &info);

    if (!info.stack_ptr) {
        log_err("No suitable memory space was found for the stack. Aborting.");
        goto terminate;
    }

    log_debug("esp: 0x%x\n", info.stack_ptr);
    //SET_ESP(info.stack_ptr);

    /* Initialize GDT */
    gdt_init();
    log_ok("Loaded GDT!\n");

terminate:
    HLT();
    for (;;);
}
