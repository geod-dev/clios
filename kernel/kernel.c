#include "clear.h"
#include "write.h"
#include "vga.h"

void kernel_main(void)
{
    clear();
    write("Hello World!");
}
