#include "keymaps.h"
#include "stdin.h"
#include "stdout.h"

int input(char *buffer, int max_length)
{
    int index = 0;

    while (index < max_length - 1) {
        char *ascii = __get_next_ascii();
        if (ascii) {
            if (*ascii == '\b') {
                if (index > 0) {
                    index--;
                    __putchar('\b');
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
