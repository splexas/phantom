#include <cpu/isr.h>
#include <lib/stdout.h>

static const exception_info_t exceptions[32] = {
    {"Division Error", true},
    {"Debug", false},
    {"Non-maskable Interrupt", false},
    {"Breakpoint", false},
    {"Overflow", false},
    {"Bound Range Exceeded", true},
    {"Invalid Opcode", true},
    {"Device Not Available", true},
    {"Double Fault", true},
    {"Coprocessor Segment Overrun", true},
    {"Invalid TSS", true},
    {"Segment Not Present", true},
    {"Stack-Segment Fault", true},
    {"General Protection Fault", true},
    {"Page Fault", true},
    {"Reserved", false},
    {"x87 Floating-Point Exception", true},
    {"Alignment Check", true},
    {"Machine Check", false},
    {"SIMD Floating-Point Exception", true},
    {"Virtualization Exception", true},
    {"Control Protection Exception", true},
    {"Reserved", false},
    {"Reserved", false},
    {"Reserved", false},
    {"Reserved", false},
    {"Reserved", false},
    {"Reserved", false},
    {"Hypervisor Injection Exception", true},
    {"VMM Communication Exception", true},
    {"Security Exception", true},
    {"Reserved", false},
};

void exception_handler(int_frame_t frame)
{
    if (exceptions[frame.int_no].panic) {
        kprintf("=== KERNEL PANIC ===\n");
        kprintf("Cause: %s (interrupt ID: %u)\n", exceptions[frame.int_no].name,
                frame.int_no);
        if (frame.err_code)
            kprintf("Error code: %u\n", frame.err_code);
        kprintf("--- Register dump ---\n");
        kprintf(" EAX: 0x%08X  EBX: 0x%08X  ECX: 0x%08X\n", frame.eax,
                frame.ebx, frame.ecx);
        kprintf(" EDX: 0x%08X  EDI: 0x%08X  ESI: 0x%08X\n", frame.edx,
                frame.edi, frame.esi);
        kprintf(" EBP: 0x%08X  ESP: 0x%08X  EIP: 0x%08X\n", frame.ebp,
                frame.esp, frame.eip);
        kprintf(" CS : 0x%08X  EFLAGS: 0x%08X\n", frame.cs, frame.eflags);
        kprintf("=====================\n");
    }
    for (;;) asm volatile("hlt");
}