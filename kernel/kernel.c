#include "kernel.h"
#include "include/multiboot2.h"
#include "include/types.h"
#include "include/vga.h"

__attribute__((noreturn)) void kmain(u32 mb2_boot, u32 mb2_magic)
{
    if (mb2_magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        kprintf("Kernel wasn't booted by GRUB Multiboot2. Aborting.");
        hlt();
        goto terminate;
    }

    if (mb2_boot & 7) {
        kprintf("Unaligned mbi: 0x%x. Aborting.\n", mb2_boot);
        hlt();
        goto terminate;
    }

    // Lower memory starts at address 0, and upper memory starts at address 1 megabyte

    u32 min_mem_addr = 0;
    u32 max_mem_addr = 1024 * 1024;

    struct multiboot_tag *tag;
    for (tag = (struct multiboot_tag *) (mb2_boot + 8);
        tag->type != MULTIBOOT_TAG_TYPE_END;
        tag = (struct multiboot_tag *)((multiboot_uint8_t *)tag + ((tag->size + 7) & ~7)))
    {
        switch (tag->type) {
            case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO: {
                struct multiboot_tag_basic_meminfo *mem = (struct multiboot_tag_basic_meminfo *)tag;
                kprintf("Mem lower: 0x%x KB\nMem higher: 0x%x KB\n", mem->mem_lower, mem->mem_upper);
                max_mem_addr += mem->mem_upper * 1024 - 1024 * 1024; // -1 megabyte memory hole
                break;
            }
            case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME: {
                kprintf("Boot loader name = %s\n",
                        ((struct multiboot_tag_string *) tag)->string);
                break;
            }
        }
    }

    u32 total_memory = max_mem_addr - min_mem_addr;
    kprintf("Total RAM: %d bytes\n", total_memory);

    // conventional memory is below 1 mb

terminate:
    for (;;);
}