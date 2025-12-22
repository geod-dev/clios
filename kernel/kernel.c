#include "commands.h"
#include "stdin.h"
#include "stdnull.h"
#include "stdout.h"
#include "strings.h"

void kernel_main(void)
{
    char buffer[256];
    int found = 0;

    clear();
    while (1) {
        write(">>");
        input(buffer, 256);
        found = 0;
        for (int i = 0; COMMANDS[i].name != NULL; i++) {
            if (strcmp(buffer, COMMANDS[i].name) == 0) {
                COMMANDS[i].func();
                found = 1;
                break;
            }
        }
        if (!found) {
            write(buffer);
            write(": command not found");
            write("\n");
        }
    }
}
