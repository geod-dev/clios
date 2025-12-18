#include "stdin.h"
#include "keymaps.h"

char *__scancode_to_ascii(char scancode)
{
    if (MAJ_PRESSED)
        return AZERTY_KEYMAP[(unsigned char)scancode].shift;
    return AZERTY_KEYMAP[(unsigned char)scancode].normal;
}
