// Source -
// https://stackoverflow.com/questions/61124564/convert-scancodes-to-ascii
// Posted by jonathan
// Retrieved 2025-12-17, License - CC BY-SA 4.0

#ifndef KEYMAPS_H
#define KEYMAPS_H
#define MAJ (void *)1

typedef struct {
    char *normal;
    char *shift;
    char *altgr;
} keymap_entry_t;

static const char QWERTY_KEYMAP[] = {\
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',\
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',\
    0, /* <-- control key */\
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z',\
    'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, /* Alt */\
    ' ',                                                    /* Space bar */\
    0,                                                      /* Caps lock */\
    0,                         /* 59 - F1 key ... > */\
    0, 0, 0, 0, 0, 0, 0, 0, 0, /* < ... F10 */\
    0,                         /* 69 - Num lock */\
    0,                         /* Scroll Lock */\
    0,                         /* Home key */\
    0,                         /* Up Arrow */\
    0,                         /* Page Up */\
    '-', 0,                    /* Left Arrow */\
    0, 0,                      /* Right Arrow */\
    '+', 0,                    /* 79 - End key*/\
    0,                         /* Down Arrow */\
    0,                         /* Page Down */\
    0,                         /* Insert Key */\
    0,                         /* Delete Key */\
    0, 0, 0, 0,                /* F11 Key */\
    0,                         /* F12 Key */\
    0,                         /* All other keys are undefined */\
};


static const keymap_entry_t EMPTY = {"", "", ""};
static const keymap_entry_t AZERTY_KEYMAP[] = {
    EMPTY, EMPTY, {"&", "1", ""}, {"é", "2", "~"}, {"\"", "3", "#"}, {"'", "4", "{"}, {"(", "5", "["}, {"-", "6", "|"}, {"è", "7", "`"}, {"_", "8", "\\"}, {"ç", "9", "^"}, {"à", "0", "@"}, {")", "°", "]"}, {"=", "+", "}"}, {"\b", "\b", "\b"}, {"\t", "\t", "\t"},
    {"a", "A", ""}, {"z", "Z", ""}, {"e", "E", ""}, {"r", "R", ""}, {"t", "T", ""}, {"y", "Y", ""}, {"u", "U", ""}, {"i", "I", ""}, {"o", "O", ""}, {"p", "P", ""}, {"^", "¨", ""}, {"$", "£", ""}, {"\n", "\n", ""},
    EMPTY,
    {"q", "Q", ""}, {"s", "S", ""}, {"d", "D", ""}, {"f", "F", ""}, {"g", "G", ""}, {"h", "H", ""}, {"j", "J", ""}, {"k", "K", ""}, {"l", "L", ""}, {"m", "M", ""}, {"ù", "%", ""}, {"*", "µ", ""}, {MAJ, MAJ, ""}, {"<", ">", ""},
    {"w", "W", ""}, {"x", "X", ""}, {"c", "C", ""}, {"v", "V", ""}, {"b", "B", ""}, {"n", "N", ""}, {",", "?", ""}, {";", ".", ""}, {":", "/", ""}, {"!", "§", ""}, {MAJ, MAJ, ""}, EMPTY, EMPTY,
    {" ", " ", " "}, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY
};

#endif // KEYMAPS_H
