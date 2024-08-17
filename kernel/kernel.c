#include "kernel.h"
#include "include/multiboot2.h"
#include "include/types.h"
#include "include/vga.h"
#include "include/gdt.h"

__attribute__((noreturn)) void kmain(u32 mb2_boot, u32 mb2_magic)
{
    if (mb2_magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        kprintf("Kernel wasn't booted by GRUB Multiboot2. Aborting.");
        hlt();
        goto terminate;
    }

    if (mb2_boot & 7) {
        kprintf("Unaligned mbi: 0x%x. Aborting.", mb2_boot);
        hlt();
        goto terminate;
    }

    u32 min_mem_addr = 0x100000;
    u32 max_mem_addr = 0;
    u8 stack_init = 0;

    struct multiboot_tag *tag;
    for (tag = (struct multiboot_tag *)(mb2_boot + 8);
        tag->type != MULTIBOOT_TAG_TYPE_END;
        tag = (struct multiboot_tag *)((multiboot_uint8_t *)tag + ((tag->size + 7) & ~7)))
    {
        switch (tag->type) {
            case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO: {
                struct multiboot_tag_basic_meminfo *mem = (struct multiboot_tag_basic_meminfo *)tag;
                max_mem_addr = mem->mem_upper * 1024;
                break;
            }
            case MULTIBOOT_TAG_TYPE_MMAP: {
                multiboot_memory_map_t *mmap;
                for (mmap = ((struct multiboot_tag_mmap *)tag)->entries;
                    (multiboot_uint8_t *)mmap < (multiboot_uint8_t *)tag + tag->size;
                    mmap = (multiboot_memory_map_t *) 
                    ((unsigned long)mmap
                        + ((struct multiboot_tag_mmap *)tag)->entry_size))
                {
                    if ((u32)mmap->addr != 0x100000 && mmap->type == MULTIBOOT_MEMORY_AVAILABLE) {
                        kprintf("Initializing the stack.\n");
                        u32 stack_ptr = (u32)mmap->addr + (u32)mmap->len;
                        asm volatile("mov %0, %%esp" :: "r"(stack_ptr));
                        stack_init = 1;
                        break;
                    }
                }
                break;
            }
        }
    }

    if (stack_init == 0) { 
        kprintf("Kernel has failed to find space for stack. Aborting.");
        hlt();
        goto terminate;
    }

    /* Initialize GDT */
    gdt_load();
    kprintf("Loaded the GDT!\n");

terminate:
    for (;;);
}
