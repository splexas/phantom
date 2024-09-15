#ifndef LOG_H
#define LOG_H

#include "core/vga.h"

#define __log_tag(color, tag, fmt, ...) \
    kprintc('[', VGA_COLOR_WHITE); \
    kprint(color, tag); \
    kprint(VGA_COLOR_WHITE, "] "); \
    kprint(VGA_COLOR_WHITE, fmt, ##__VA_ARGS__); \

#define log_ok(fmt, ...) do { \
    __log_tag(VGA_COLOR_GREEN, "OK", fmt, ##__VA_ARGS__); \
} while (0)

#define log_err(fmt, ...) do { \
    __log_tag(VGA_COLOR_RED, "ERROR", fmt, ##__VA_ARGS__); \
} while (0)

#define log_warn(fmt, ...) do { \
    __log_tag(VGA_COLOR_YELLOW, "WARNING", fmt, ##__VA_ARGS__); \
} while (0)

#define log_info(fmt, ...) do { \
    __log_tag(VGA_COLOR_LIGHT_GREY, "INFO", fmt, ##__VA_ARGS__); \
} while (0)

#define log_debug(fmt, ...) do { \
    __log_tag(VGA_COLOR_DARK_GREY, "DEBUG", fmt, ##__VA_ARGS__); \
} while (0)

#endif