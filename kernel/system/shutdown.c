static inline void outw(unsigned short port, unsigned short value)
{
    asm volatile("outw %0, %1" : : "a"(value), "Nd"(port));
}

void shutdown(void)
{
    outw(0x604, 0x2000);
    outw(0xB004, 0x2000);
    while (1)
        asm volatile("hlt");
}
