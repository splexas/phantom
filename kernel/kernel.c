#include <cpu/gdt.h>
#include <cpu/idt.h>

#include <multiboot2.h>
#include <stdint.h>

#include <lib/stdout.h>
#include <video/serial.h>
#include <video/vga.h>

__attribute__((noreturn)) void kmain(uint32_t magic, uint32_t mb_info_addr)
{
    vga_init();
    stdout_set_stream(vga_putchar);

    kprintf("Serial\n");

    if (serial_init() != 0) {
        kprintf("Failed to initialize serial monitor.\n");
        goto idle;
    }

    stdout_set_stream(serial_putchar);

    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        kprintf("Invalid magic number: %x\n", magic);
        goto idle;
    }

    if (mb_info_addr & 7) {
        kprintf("Unaligned mbi: %x\n", mb_info_addr);
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
            kprintf("basic_meminfo:\n");
            kprintf("  mem_lower=%x\n", meminfo->mem_lower);
            kprintf("  mem_upper=%x\n", meminfo->mem_upper);
            break;
        }
        case MULTIBOOT_TAG_TYPE_MMAP: {

            multiboot_memory_map_t *mmap;

            kprintf("mmap:\n");

            for (mmap = ((struct multiboot_tag_mmap *)tag)->entries;
                 (multiboot_uint8_t *)mmap <
                 (multiboot_uint8_t *)tag + tag->size;
                 mmap =
                     (multiboot_memory_map_t
                          *)((uint32_t)mmap +
                             ((struct multiboot_tag_mmap *)tag)->entry_size)) {

                kprintf("  base_addr=%x,"
                        " length=%x, type=%x\n",
                        (uint32_t)mmap->addr, (uint32_t)mmap->len, mmap->type);
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
    kprintf("GDT was initialized\n");
    idt_init();
    kprintf("IDT was initialized\n");

idle:
    for (;;)
        ;
}