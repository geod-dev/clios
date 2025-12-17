#include "stdin.h"
#include "stdout.h"

void kernel_main(void)
{
    char buffer[256];

    clear();
    while (1) {
        write(">>");
        input(buffer, 256);
        write(buffer);
        write("\n");
    }
}
