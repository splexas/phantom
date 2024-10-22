#include <cpu/irq.h>
#include <cpu/pic.h>
#include <io.h>
#include <lib/stdout.h>

#include <cpu/irqs/keyboard.h>

void irq_handler(uint32_t num)
{
    switch (num) {
    case 0x01: {
        kb_handle(num);
        break;
    }
    }

    pic_send_eoi(num);
}