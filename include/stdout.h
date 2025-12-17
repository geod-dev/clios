#ifndef STDOUT_H
#define STDOUT_H
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY_ADDRESS ((volatile char *)0xB8000)
void clear(void);
void write(const char *str);
#endif // STDOUT_H
