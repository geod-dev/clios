#include "stdin.h"

void __wait_for_keypress()
{
    while (!(__get_next_scancode(KEYBOARD_STATUS) & 1));
}
