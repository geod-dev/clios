#include "system.h"

void shutdown(void)
{
    __outw(0x604, 0x2000);
    __outw(0xB004, 0x2000);
    while (1)
        asm volatile("hlt");
}
