#include <multiboot2.h>
#include <stdint.h>
#include <video/vga.h>

struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

__attribute__((noreturn)) void kmain(uint32_t magic,
                                     struct multiboot_info *mb_info_addr)
{
    vga_init();
    for (;;)
        ;
}