.global enable_long_mode
.extern kernel_main
.extern setup_paging
.extern gdt_enable_long_mode
.extern pml4

.section .text
.code32
enable_long_mode:
    call setup_paging

    # Load PML4 into CR3
    mov $pml4, %eax
    mov %eax, %cr3

    # Enable PAE in CR4
    mov %cr4, %eax
    or $0x20, %eax
    mov %eax, %cr4

    # Enable Long Mode in EFER MSR
    mov $0xC0000080, %ecx
    rdmsr
    or $0x100, %eax
    wrmsr

    # Enable Paging in CR0
    mov %cr0, %eax
    or $0x80000000, %eax
    mov %eax, %cr0

    # Far jump to flush prefetch queue and switch to long mode
    call gdt_enable_long_mode
    ljmp $0x08, $long_mode_start
.code64
long_mode_start:
    # 1. Clear Segment Registers
    xor %ax, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss

    # 2. Setup Stack
    # Loading into %eax clears the upper bits of %rax automatically.
    # This generates a 32-bit relocation which is valid in your object file.
    mov $stack_top, %eax
    mov %rax, %rsp

    # 3. Relocate Kernel
    # We load addresses into 32-bit registers (esi, edi, ecx).
    # This ensures RSI, RDI, RCX are clean (upper bits zeroed).
    mov $kernel_binary_start, %esi
    mov $0x200000, %edi
    
    # Calculate size
    mov $kernel_binary_end, %ecx
    sub %esi, %ecx
    
    # 'rep movsb' uses RCX, RSI, RDI (which are now valid 64-bit pointers)
    cld
    rep movsb

    # 4. Jump to Kernel
    mov $0x200000, %eax
    call *%rax
    hlt

.align 4096
kernel_binary_start:
    .incbin "build/kernel.bin"
kernel_binary_end:

.section .bss
.align 16
stack_bottom:
    .skip 16384
stack_top:
