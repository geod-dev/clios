#include "clear.h"
#include "vga.h"

void clear(void)
{
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i++)
        VGA_MEMORY_ADDRESS[i] = 0;
}
