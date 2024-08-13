#ifndef VGA_H
#define VGA_H

#include "types.h"

#define VIDEO_MEMORY 0xb8000 
#define MAX_COLUMNS 80

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

struct vga_char {
    u8 ch;
    u8 color;
};

#define kprintf(fmt, ...) kprint(VGA_COLOR_WHITE, fmt, ##__VA_ARGS__);

void kprintc(u8 ch, u8 color);
void kprintint(u32 num, u8 color);
void kprinthex(u32 num, u8 color);
void kprint(u8 color, u8 *fmt, ...);

#endif