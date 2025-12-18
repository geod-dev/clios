#include "stdout.h"

static int handle_special_char(char c)
{
    if (c == '\n') {
        int col = (CURSOR_POSITION / 2) % VGA_WIDTH;
        CURSOR_POSITION += (VGA_WIDTH - col) * 2;
        return 1;
    }
    if (c == '\b') {
        if (CURSOR_POSITION >= 2) {
            CURSOR_POSITION -= 2;
            VGA_MEMORY_ADDRESS[CURSOR_POSITION] = ' ';
            VGA_MEMORY_ADDRESS[CURSOR_POSITION + 1] = 0x0F; // White on black
        }
        return 1;
    }
    return 0;
}

void __putchar(char c)
{
    if (!handle_special_char(c)) {
        VGA_MEMORY_ADDRESS[CURSOR_POSITION] = c;
        VGA_MEMORY_ADDRESS[CURSOR_POSITION + 1] = 0x0F; // White on black
        CURSOR_POSITION += 2;
    }
    if (CURSOR_POSITION >= VGA_WIDTH * VGA_HEIGHT * 2) {
        __scroll();
    }
}
