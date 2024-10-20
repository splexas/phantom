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