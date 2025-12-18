#include "stdout.h"

void __scroll(void)
{
    int line_size = VGA_WIDTH * 2;
    int screen_size = VGA_WIDTH * VGA_HEIGHT * 2;

    // Move lines 1..end to lines 0..end-1
    for (int i = 0; i < screen_size - line_size; i++) {
        VGA_MEMORY_ADDRESS[i] = VGA_MEMORY_ADDRESS[i + line_size];
    }

    // Clear last line
    for (int i = screen_size - line_size; i < screen_size; i += 2) {
        VGA_MEMORY_ADDRESS[i] = ' ';
        VGA_MEMORY_ADDRESS[i + 1] = 0x0F;
    }

    CURSOR_POSITION = screen_size - line_size;
}
