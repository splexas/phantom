#ifndef MB2_H
#define MB2_H

#include <types.h>

struct mb2_info {
    u32 mem_base_addr;
    u32 mem_base_len;
    u32 stack_ptr;
};

void mb2_parse(u32 mb2_boot_addr, struct mb2_info *info);

#endif