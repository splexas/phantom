#include <vga.h>
#include <stdarg.h>

static u32 cursor_x = 0;
static u32 cursor_y = 0;

void kclear()
{
    struct vga_char* video = (struct vga_char*)VIDEO_MEMORY;
    for (int i = 0; i < VIDEO_WIDTH * VIDEO_HEIGHT; i++)
        video[i].character = ' ';
}

static void kprintc(s8 color, char c)
{
    struct vga_char* video = (struct vga_char*)VIDEO_MEMORY;
    int index = cursor_x + cursor_y * VIDEO_WIDTH;
    video[index].character = c;
    video[index].color = color;
    cursor_x++;
}

static int cdigits(int digit)
{
    int res = 0;
    while (digit > 0) {
        digit /= 10;
        res++;
    }
    return res;
}

void kprint(s8 color, const s8* msg, ...)
{
    va_list args;
    va_start(args, msg);
    while (*msg != 0) {
        if (*msg == '%') {
            msg++;
            switch (*msg) {
                case 's': {
                    msg++;
                    const s8* tmp = va_arg(args, const s8*);
                    while (*tmp)
                        kprintc(color, *tmp++);
                    break;
                }
                case 'd': {
                    msg++;
                    char buf[10];
                    s32 num = va_arg(args, s32);
                    int digits = cdigits(num);
                    for (int i = 0; i < digits; i++) {
                        buf[i] = num % 10 + '0';
                        num /= 10;
                    }
                    for (int i = digits - 1; i >= 0; i--)
                        kprintc(color, buf[i]);
                    break;
                }
                case 'x': {
                    break;
                }
            }
            continue;
        }
        /* New line management */
        if (cursor_x == VIDEO_WIDTH || *msg == '\n') {
            cursor_x = 0;
            cursor_y += 1;
            if (*msg == '\n') {
                msg++;
                continue;
            }
        }
        kprintc(color, *msg++);
    }
    va_end(args);
}

void klog(const s8* tag, const s8* msg)
{
    kprint(VGA_WHITE, tag);
    kprint(VGA_WHITE, ": ");
    kprint(VGA_GRAY, msg);
    kprint(VGA_GRAY, "\n");
}

void kdisplay_logo()
{
    const s8* logo = (
        " _____  _                 _\n"                  
        "|  __ \\| |               | |\n"                 
        "| |__) | |__   __ _ _ __ | |_ ___  _ __ ___\n"
        "|  ___/| '_ \\ / _` | '_ \\| __/ _ \\| '_ ` _ \\\n" 
        "| |    | | | | (_| | | | | || (_) | | | | | |\n"
        "|_|    |_| |_|\\__,_|_| |_|\\__\\___/|_| |_| |_|\n"
    );
    kprint(VGA_WHITE, logo);
}
