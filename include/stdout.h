#ifndef STDOUT_H
#define STDOUT_H
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
static volatile unsigned char *VGA_MEMORY_ADDRESS = (volatile unsigned char *)0xB8000;
static int CURSOR_POSITION = 0;
void clear(void);
void putchar(char c);
int write(const char *str);
int writen(const char *str, int n);
#endif // STDOUT_H
