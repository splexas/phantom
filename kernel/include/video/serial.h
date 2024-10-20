#ifndef _VIDEO_SERIAL_H
#define _VIDEO_SERIAL_H

#include <io.h>

#define COM1 0x3f8

int serial_init();
int serial_received();
char serial_readchar();
int serial_is_transmit_empty();
void serial_putchar(char c);

#endif