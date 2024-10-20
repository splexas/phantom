#ifndef _CPU_ISR_H
#define _CPU_ISR_H

#include <stdint.h>

typedef struct interrupt_frame {
    uint32_t int_no;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t err_code, eip, cs, eflags;
} __attribute__((packed)) int_frame_t;

void exception_handler(int_frame_t frame);

#endif