#include "stdout.h"

int write(const char *str)
{
    int i = 0;
    for (; str[i] != '\0'; i++)
        __putchar(str[i]);
    return i;
}
