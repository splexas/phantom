#ifndef ISR_H
#define ISR_H

extern void _isr_handler(); // in stub

extern void isr_handler(); // from stub to this
extern void exception_handler();

#endif