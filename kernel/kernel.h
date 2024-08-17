#ifndef KERNEL_H
#define KERNEL_H

#include "include/types.h"

#define HLT() asm volatile ("hlt")
#define SET_ESP(val) asm volatile("mov %0, %%esp" :: "r"(val))

#endif