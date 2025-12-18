#ifndef STDIN_H
#define STDIN_H
#define KEYBOARD_DATA 0x60
#define KEYBOARD_STATUS 0x64
extern int MAJ_PRESSED;
char *__scancode_to_ascii(char scancode);
unsigned char __get_next_scancode(unsigned short port);
void __wait_for_keypress();
char *__get_next_ascii();
int input(char *buffer, int max_length);
#endif // STDIN_H
