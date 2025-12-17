#include "write.h"
#include "vga.h"

void write(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        VGA_MEMORY_ADDRESS[i * 2] = str[i];
        VGA_MEMORY_ADDRESS[i * 2 + 1] = 0x0F;
    }
}
