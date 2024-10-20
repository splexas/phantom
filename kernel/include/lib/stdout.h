#ifndef _LIB_STDOUT_H
#define _LIB_STDOUT_H

#include <stdarg.h>

void stdout_set_stream(void (*putch)(char c));
void kprintf(const char *fmt, ...);

#endif