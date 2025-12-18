#ifndef COMMANDS_H
#define COMMANDS_H
#include "stdnull.h"
#include "system.h"

typedef struct command_s {
    char *name;
    void (*func)();
} command_t;

static const command_t COMMANDS[] = {
    {"shutdown", shutdown},
    {NULL, NULL}
};
#endif // COMMANDS_H
