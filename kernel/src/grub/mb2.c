#include <grub/mb2.h>
#include <grub/multiboot2.h>

void mb2_parse(u32 mb2_boot_addr, struct mb2_info *info)
{
    info->mem_base_addr = 0x100000;
    struct multiboot_tag *tag;
    for (tag = (struct multiboot_tag *)(mb2_boot_addr + 8);
        tag->type != MULTIBOOT_TAG_TYPE_END;
        tag = (struct multiboot_tag *)((multiboot_uint8_t *)tag + ((tag->size + 7) & ~7)))
    {
        switch (tag->type) {
            case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO: {
                struct multiboot_tag_basic_meminfo *mem = (struct multiboot_tag_basic_meminfo *)tag;
                info->mem_base_len = (mem->mem_upper * 1024) - info->mem_base_addr;
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
                        info->stack_ptr = (u32)mmap->addr + (u32)mmap->len;
                        break;
                    }
                }
                break;
            }
        }
    }
}