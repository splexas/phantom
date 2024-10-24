#include <lib/stdout.h>
#include <stdarg.h>
#include <video/serial.h>

#define NANOPRINTF_IMPLEMENTATION
#include <nanoprintf.h>

static npf_putc __DEFAULT_STDOUT = NULL;

void stdout_set_stream(void (*putch)(char c))
{
    __DEFAULT_STDOUT = (npf_putc)putch;
}

void kvprintf(const char *fmt, va_list args)
{
    if (__DEFAULT_STDOUT == NULL)
        return;

    npf_vpprintf(__DEFAULT_STDOUT, NULL, fmt, args);
}

void kprintf(const char *fmt, ...)
{
    if (__DEFAULT_STDOUT == NULL)
        return;

    va_list list;
    va_start(list, fmt);
    kvprintf(fmt, list);
    va_end(list);
}