#include "stdin.h"
#include "keymaps.h"

static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static char get_scancode() {
    // Wait until output buffer full
    while (!(inb(KEYBOARD_STATUS) & 1));
    return inb(KEYBOARD_DATA);
}

char scancode_to_ascii(char scancode) {
    if (scancode < 0 || scancode > 83) {
        return 0; // Undefined scancode
    }
    return AZERTY_KEYMAP[(unsigned char)scancode];
}

int input(char *buffer, int max_length) {
    int index = 0;

    for (; index < max_length - 1; index++) {
        char scancode = get_scancode();
        char ascii = scancode_to_ascii(scancode);
        if (ascii) {
            buffer[index] = ascii;
            if (ascii == '\n')
                break;
        }
    }
    buffer[index] = '\0';
    return index;
}
