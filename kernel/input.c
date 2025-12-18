#include "keymaps.h"
#include "stdin.h"
#include "stdout.h"

static int MAJ_PRESSED = 0;

static inline unsigned char get_next_scancode(unsigned short port)
{
    unsigned char ret;
    __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static char *scancode_to_ascii(char scancode)
{
    if (MAJ_PRESSED)
        return AZERTY_KEYMAP[(unsigned char)scancode].shift;
    return AZERTY_KEYMAP[(unsigned char)scancode].normal;
}

static void wait_for_keypress()
{
    while (!(get_next_scancode(KEYBOARD_STATUS) & 1));
}

static char *get_next_ascii()
{
    unsigned char scancode = 0;
    wait_for_keypress();
    while (1) {
        scancode = get_next_scancode(KEYBOARD_DATA);
        if (scancode >= 0x80 && MAJ_PRESSED && scancode_to_ascii(scancode - 0x80) == (char *)1) {
            MAJ_PRESSED = 0;
            continue;
        }
        if (scancode >= 0x80 || scancode == 0xE0 || scancode == 0xE1 ||
            scancode == 0)
            continue;
        char *ascii = scancode_to_ascii(scancode);
        if (ascii == (char *)1) {
            MAJ_PRESSED = 1;
            wait_for_keypress();
            continue;
        }
        if (!ascii || !*ascii)
            continue;
        if (ascii > (char *)1)
            return ascii;
    }
}

int input(char *buffer, int max_length)
{
    int index = 0;

    while (index < max_length - 1) {
        char *ascii = get_next_ascii();
        if (ascii) {
            if (*ascii == '\b') {
                if (index > 0) {
                    index--;
                    putchar('\b');
                }
                continue;
            }
            write(ascii);
            if (*ascii == '\n')
                break;
            for (int i = 0; ascii[i] != '\0'; i++)
                if (index >= max_length - 1)
                    break;
                else
                    buffer[index++] = ascii[i];
        }
    }
    buffer[index] = '\0';
    return index;
}
