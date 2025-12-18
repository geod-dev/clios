#include "system.h"

void __outw(unsigned short port, unsigned short value)
{
    asm volatile("outw %0, %1" : : "a"(value), "Nd"(port));
}
