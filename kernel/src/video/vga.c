#include <io.h>
#include <stdint.h>
#include <video/vga.h>

volatile uint16_t *vga_buf = (volatile uint16_t *)VGA_TEXT_BUFFER;
static uint32_t row = 0;
static uint32_t col = 0;

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char c, enum vga_color color)
{
    return (uint16_t)c | (uint16_t)color << 8;
}

static void vga_disable_cursor()
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

static void vga_clear()
{
    for (uint32_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
        vga_buf[i] = vga_entry(' ', VGA_COLOR_WHITE);
}

void vga_init()
{
    vga_disable_cursor();
    vga_clear();
}

void vga_putchar(char c)
{
    if (c == '\n') {
        row++;
        col = 0;
    }
    else {
        const uint32_t index = row * VGA_WIDTH + col;
        vga_buf[index] = vga_entry(c, VGA_COLOR_WHITE);
        if (++col == VGA_WIDTH) {
            col = 0;
            if (++row == VGA_HEIGHT)
                row = 0;
        }
    }
}

void vga_vprintf(const char *fmt, va_list list)
{
    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
            case 'c': {
                char c = (char)va_arg(list, int);
                vga_putchar(c);
                break;
            }
            case 's': {
                char *str = va_arg(list, char *);
                while (*str)
                    vga_putchar(*str++);
                break;
            }
            case 'd': {
                int num = va_arg(list, int);
                if (num < 0) {
                    vga_putchar('-');
                    num = -num;
                }
                char buf[11]; // enough for 32-bit int
                unsigned long i = 0;
                do {
                    buf[i++] = (num % 10) + '0';
                    num /= 10;
                } while (num && i < sizeof(buf));

                while (i > 0)
                    vga_putchar(buf[--i]);
                break;
            }
            case 'u': {
                unsigned int num = va_arg(list, unsigned int);
                if (num == 0) {
                    vga_putchar('0');
                    break;
                }
                char buf[11];
                unsigned long i = 0;
                do {
                    buf[i++] = (num % 10) + '0';
                    num /= 10;
                } while (num && i < sizeof(buf));

                while (i > 0)
                    vga_putchar(buf[--i]);
                break;
            }
            case 'p':
            case 'x': {
                unsigned int num = va_arg(list, unsigned int);
                vga_putchar('0');
                vga_putchar('x');

                char buf[8];
                for (int i = 7; i >= 0; --i) {
                    buf[i] = "0123456789abcdef"[num & 0xf];
                    num >>= 4;
                }

                int start = 0;
                while (start < 8 && buf[start] == '0')
                    start++;

                if (start == 8)
                    vga_putchar('0');
                else
                    for (int j = start; j < 8; j++)
                        vga_putchar(buf[j]);
                break;
            }
            case '%': {
                vga_putchar('%');
                break;
            }
            default:
                vga_putchar('%');
                vga_putchar(*fmt);
            }
        }
        else {
            vga_putchar(*fmt);
        }
        fmt++;
    }
}

void vga_printf(const char *fmt, ...)
{
    va_list list;
    va_start(list, fmt);
    vga_vprintf(fmt, list);
    va_end(list);
}