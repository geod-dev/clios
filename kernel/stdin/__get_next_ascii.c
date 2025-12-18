#include "stdin.h"

char *__get_next_ascii()
{
    unsigned char scancode = 0;
    __wait_for_keypress();
    while (1) {
        scancode = __get_next_scancode(KEYBOARD_DATA);
        if (scancode >= 0x80 && MAJ_PRESSED && __scancode_to_ascii(scancode - 0x80) == (char *)1) {
            MAJ_PRESSED = 0;
            continue;
        }
        if (scancode >= 0x80 || scancode == 0xE0 || scancode == 0xE1 ||
            scancode == 0)
            continue;
        char *ascii = __scancode_to_ascii(scancode);
        if (ascii == (char *)1) {
            MAJ_PRESSED = 1;
            __wait_for_keypress();
            continue;
        }
        if (!ascii || !*ascii)
            continue;
        if (ascii > (char *)1)
            return ascii;
    }
}
