#include <core/tss.h>

void tss_load(u32 esp0)
{
    tss.link = 0;
    tss.esp0 = esp0;
    // more stuff
}

void tss_init()
{
    
}

