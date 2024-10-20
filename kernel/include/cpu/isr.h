#ifndef _CPU_ISR_H
#define _CPU_ISR_H

#include <stdbool.h>
#include <stdint.h>

typedef struct interrupt_frame {
    uint32_t int_no;
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t err_code;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
} __attribute__((packed)) int_frame_t;

typedef struct exception_info {
    const char *name;
    bool panic;
} exception_info_t;

void exception_handler(int_frame_t frame);

#endif