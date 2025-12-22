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

# Set up a stack
.section .bss
.align 16
stack_bottom:
    .skip 16384 # 16 Ko stack
stack_top:

.section .text
.global _start  
_start:
    mov $stack_top, %esp # Initialize stack pointer
    cli
    call gdt_install
    mov $0xB8000, %edi
    mov $'A', %al
    mov $0x07, %ah
    stosw
    call enable_long_mode
    mov $0xB8000, %edi
    mov $'B', %al
    mov $0x07, %ah
    stosw

    jmp halt_end

halt_end:
    hlt
    jmp halt_end
