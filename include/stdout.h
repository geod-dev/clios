#ifndef STDOUT_H
#define STDOUT_H
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static volatile unsigned char *VGA_MEMORY_ADDRESS =
    (volatile unsigned char *)0xB8000;
extern int CURSOR_POSITION;

void __putchar(char c);
void __scroll(void);
void clear(void);
int write(const char *str);
#endif // STDOUT_H
