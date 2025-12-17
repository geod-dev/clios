#include "stdout.h"

static void scroll(void)
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

void putchar(char c)
{
    if (!handle_special_char(c)) {
        VGA_MEMORY_ADDRESS[CURSOR_POSITION] = c;
        VGA_MEMORY_ADDRESS[CURSOR_POSITION + 1] = 0x0F; // White on black
        CURSOR_POSITION += 2;
    }
    if (CURSOR_POSITION >= VGA_WIDTH * VGA_HEIGHT * 2) {
        scroll();
    }
}

int write(const char *str)
{
    int i = 0;
    for (; str[i] != '\0'; i++)
        putchar(str[i]);
    return i;
}
