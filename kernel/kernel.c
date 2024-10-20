#include <cpu/gdt.h>
#include <cpu/idt.h>

#include <multiboot2.h>
#include <stdint.h>
#include <video/vga.h>

__attribute__((noreturn)) void kmain(uint32_t magic, uint32_t mb_info_addr)
{
    vga_init();
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        vga_printf("Invalid magic number: %x\n", magic);
        goto idle;
    }

    if (mb_info_addr & 7) {
        vga_printf("Unaligned mbi: %x\n", mb_info_addr);
        goto idle;
    }

    struct multiboot_tag *tag;
    for (tag = (struct multiboot_tag *)(mb_info_addr + 8);
         tag->type != MULTIBOOT_TAG_TYPE_END;
         tag = (struct multiboot_tag *)((multiboot_uint8_t *)tag +
                                        ((tag->size + 7) & ~7))) {

        switch (tag->type) {
        case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO: {
            struct multiboot_tag_basic_meminfo *meminfo =
                (struct multiboot_tag_basic_meminfo *)tag;
            vga_printf("basic_meminfo:\n");
            vga_printf("  mem_lower=%x\n", meminfo->mem_lower);
            vga_printf("  mem_upper=%x\n", meminfo->mem_upper);
            break;
        }
        case MULTIBOOT_TAG_TYPE_MMAP: {

            multiboot_memory_map_t *mmap;

            vga_printf("mmap:\n");

            for (mmap = ((struct multiboot_tag_mmap *)tag)->entries;
                 (multiboot_uint8_t *)mmap <
                 (multiboot_uint8_t *)tag + tag->size;
                 mmap =
                     (multiboot_memory_map_t
                          *)((uint32_t)mmap +
                             ((struct multiboot_tag_mmap *)tag)->entry_size)) {

                vga_printf("  base_addr=%x,"
                           " length=%x, type=%x\n",
                           (uint32_t)mmap->addr, (uint32_t)mmap->len,
                           mmap->type);
            }

            break;
        }
        default:
            break;
        }

        tag = (struct multiboot_tag *)((multiboot_uint8_t *)tag +
                                       ((tag->size + 7) & ~7));
    }

    gdt_init();
    vga_printf("GDT was initialized\n");
    idt_init();
    vga_printf("IDT was initialized\n");

idle:
    for (;;)
        ;
}