#include <cpu/isr.h>
#include <lib/stdout.h>

static const char *exception_names[32] = {"Division By Zero",
                                          "Debug",
                                          "Nonmaskable Interrupt",
                                          "Breakpoint",
                                          "Overflow",
                                          "Bound Range Exceeded",
                                          "Invalid Opcode",
                                          "Device Not Available",
                                          "Double Fault",
                                          "Coprocessor Segment Overrun",
                                          "Invalid TSS",
                                          "Segment Not Present",
                                          "Stack Segment Fault",
                                          "General Protection Fault",
                                          "Page Fault",
                                          "Reserved",
                                          "x87 FPU Error",
                                          "Alignment Check",
                                          "Machine Check",
                                          "Simd Exception",
                                          "Virtualization Exception",
                                          "Control Protection Exception",
                                          "Reserved",
                                          "Reserved",
                                          "Reserved",
                                          "Reserved",
                                          "Reserved",
                                          "Reserved",
                                          "Hypervisor Injection Exception",
                                          "VMM Communication Exception",
                                          "Security Exception",
                                          "Reserved"};

void exception_handler(int_frame_t frame)
{
    kprintf(
        "Exception (int_no: %u (%s), err: %u):\n  edi: 0x%08x, esi: 0x%08x, ebp: 0x%08x, "
        "esp: "
        "0x%08x\n  ebx: 0x%08x, edx: 0x%08x, ecx: 0x%08x, eax: 0x%08x\n  eip: 0x%08x, cs: 0x%08x, eflags: 0x%08x\n",
        frame.int_no, exception_names[frame.int_no], frame.err_code, frame.edi,
        frame.esi, frame.ebp, frame.esp, frame.ebx, frame.edx, frame.ecx,
        frame.eax, frame.eip, frame.cs, frame.eflags);
    asm volatile("hlt;");
}