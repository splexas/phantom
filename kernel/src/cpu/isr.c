#include <cpu/isr.h>
#include <video/vga.h>

void exception_handler(int_frame_t frame)
{
    vga_printf("Exception: int_no: %u, err: %u, eip: %p\n", frame.int_no,
               frame.err_code, frame.eip);
    asm volatile("hlt;");
}