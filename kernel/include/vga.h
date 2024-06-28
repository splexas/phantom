#ifndef VGA_H
#define VGA_H

#include <types.h>

#define VIDEO_MEMORY 0xB8000
#define VIDEO_WIDTH 80
#define VIDEO_HEIGHT 25

enum vga_color {
    VGA_BLACK,
    VGA_BLUE,
    VGA_GREEN,
    VGA_CYAN,
    VGA_RED,
    VGA_PURPLE,
    VGA_BROWN,
    VGA_GRAY,
    VGA_DARK_GRAY,
    VGA_LIGHT_BLUE,
    VGA_LIGHT_GREEN,
    VGA_LIGHT_CYAN,
    VGA_LIGHT_RED,
    VGA_LIGHT_PURPLE,
    VGA_YELLOW,
    VGA_WHITE
};

struct vga_char {
    u8 character;
    u8 color;
};

void kclear();
void kprint(s8 color, const s8* msg, ...);
void klog(const s8* tag, const s8* msg);
void kdisplay_logo();

#endif
