#define video_memory ((volatile char *)0xB8000)

static void write(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        video_memory[i * 2] = str[i];
        video_memory[i * 2 + 1] = 0x0F;
    }
}

void kernel_main(void)
{
    write("Hello World!\n");
}
