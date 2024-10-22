#ifndef _CPU_IRQS_KEYBOARD_H
#define _CPU_IRQS_KEYBOARD_H

#include <stdint.h>

char kb_get_key(uint8_t scan_code);
void kb_handle(uint8_t scan_code);

#endif