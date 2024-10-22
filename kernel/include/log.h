#ifndef _LOG_H
#define _LOG_H

#include <lib/stdout.h>

enum klog_type {
    KLOG_INFO,
    KLOG_DEBUG,
    KLOG_TRACE,
    KLOG_WARN,
    KLOG_ERROR,
    KLOG_FATAL,
};

static const char *type_tags[] = {
    "INFO",
    "DEBUG",
    "TRACE",
    "WARN",
    "ERROR",
    "FATAL"
};

#define klog(type, fmt, ...) do { \
    kprintf("[%-5s] [%s:%d] " fmt "", type_tags[type], __FILE__, __LINE__, ##__VA_ARGS__); \
} while (0)

#endif