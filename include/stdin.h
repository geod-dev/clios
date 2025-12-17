#ifndef STDIN_H
#define STDIN_H
#define KEYBOARD_DATA 0x60
#define KEYBOARD_STATUS 0x64
int input(char *buffer, int max_length);
char scancode_to_ascii(char scancode);
#endif // STDIN_H
