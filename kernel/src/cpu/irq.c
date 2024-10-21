#include <cpu/irq.h>
#include <cpu/pic.h>
#include <lib/stdout.h>

void irq_handler(uint32_t num)
{
    kprintf("Got %u IRQ\n", num);
    pic_send_eoi(num);
}