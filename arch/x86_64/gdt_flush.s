.code32
.global gdt_flush
gdt_flush:
    cli
    mov 4(%esp), %eax # load address of gdt_ptr (passed as first argument) into eax
    lgdt (%eax)       # load the GDT from the address in eax
    
    # put 0x10 in data segments (DS, ES, FS, GS, SS) to use the new GDT data segment
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    
    # far jump to reload code segment (CS) with new GDT code segment
    ljmp $0x08, $flush_done

flush_done:
    ret
