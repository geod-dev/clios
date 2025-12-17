OUTPUT_FORMAT("elf64-x86-64")
ENTRY(_start)

SECTIONS {
    . = 0x100000; /* Load address */

    .multiboot : {
        *(.multiboot)
    }

    .text : {
        *(.text*)
    }

    .rodata : {
        *(.rodata*)
    }

    .data : {
        *(.data*)
    }

    .bss : {
        *(.bss*)
        *(COMMON)
    }
}
