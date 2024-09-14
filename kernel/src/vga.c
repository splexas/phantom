#include "../include/vga.h"
#include <stdarg.h>

static u32 cursor_x = 0; // cannot be > MAX_COLUMNS
static u32 cursor_y = 0;

static void newline() {
    cursor_x = 0;
    cursor_y++;
}

void kprintc(s8 ch, u8 color)
{
    u32 index = cursor_x++ + cursor_y * MAX_COLUMNS;
    struct vga_char *vga = (struct vga_char *)VIDEO_MEMORY;
    vga[index].ch = (u8)ch;
    vga[index].color = color;
}

void kprintuint(u32 num, u8 color)
{
    if (num == 0) {
        kprintc('0', color);
        return;
    }
    char buf[10];
    int i = 0;
    while (num > 0) {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }
    for (int j = i - 1; j >= 0; j--)
        kprintc(buf[j], color);
}

void kprintsint(s32 num, u8 color)
{
    if (num == 0) {
        kprintc('0', color);
        return;
    }

    if (num < 0) {
        kprintc('-', color);
        num = -num;
    }

    char buf[10];
    int i = 0;
    while (num > 0) {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }
    for (int j = i - 1; j >= 0; j--)
        kprintc(buf[j], color);
}

void kprinthex(u32 num, u8 color) {
    char hex_digits[] = "0123456789ABCDEF";
    if (num == 0) {
        kprintc('0', color);
        return;
    }
    char buf[8]; 
    int i = 0;
    while (num > 0) {
        buf[i++] = hex_digits[num % 16];
        num /= 16;
    }
    for (int j = i - 1; j >= 0; j--)
        kprintc(buf[j], color);
}

void kprint(u8 color, s8 *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    while (*fmt) {
        if (cursor_x > MAX_COLUMNS) 
            newline();

        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case 's': {
                    fmt++;
                    const s8 *str = va_arg(args, const s8 *);
                    while (*str)
                        kprintc(*str++, color);
                    break;
                }
                case 'd': {
                    fmt++;
                    s32 num = va_arg(args, s32);
                    kprintsint(num, color);
                    break;
                }
                case 'u': {
                    fmt++;
                    u32 num = va_arg(args, u32);
                    kprintuint(num, color);
                    break;
                }
                case 'x': {
                    fmt++;
                    u32 hex_num = va_arg(args, u32);
                    kprinthex(hex_num, color);
                    break;
                }
                case 'p': {
                    fmt++;
                    u32 hex_num = va_arg(args, u32);
                    kprint(color, "0x");
                    kprinthex(hex_num, color);
                    break;
                }
            }
            continue;
        }
        if (*fmt == '\n') {
            fmt++; 
            newline();
            continue;
        }
        kprintc(*fmt++, color);
    }

    va_end(args);
}