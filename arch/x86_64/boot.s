.code32
.section .multiboot
.align 8

multiboot_header:
    .long 0xE85250D6                    # Multiboot2 magic number
    .long 0                             # architecture (0 = i386)
    .long header_end - multiboot_header # length of the header
    .long -(0xE85250D6 + 0 + (header_end - multiboot_header))  # checksum
    
    # End tag
    .align 8
    .short 0    # type
    .short 0    # flags
    .long 8     # size

header_end:

.section .text
.global _start  
_start:
    cli
    call kernel_main
hang:
    hlt
    jmp hang
