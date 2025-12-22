#define uint8_t unsigned char
#define uint16_t unsigned short
#define uint32_t unsigned int

/*
For compatibility reasons, limits and base are split into parts.
limit: 20 bits (16 bits limit_low + 4 bits from granularity (if granularity bit
    set, limit *= 4096)) = size of the segment
base: 32 bits (16 bits base_low + 8 bits base_middle + 8 bits base_high)
    = starting address of the segment
*/
struct gdt_entry {
    uint16_t limit_low;  // lower 16 bits of segment limit
    uint16_t base_low;   // lower 16 bits of base address
    uint8_t base_middle; // next 8 bits of base
    uint8_t access; // access flags (Present, Privilege(2), Type (Code or Data),
                    // Executable, DC (executable from lower privilege), RW
                    // (readable for code, writable for data), Accessed)
    uint8_t granularity; // limit upper 4 bits + flags (Granularity (* 4096),
                         // 32bit, 64 bit, available)
    uint8_t base_high;   // last 8 bits of base
} __attribute__((packed));

struct gdt_ptr {
    uint16_t limit; // size of GDT - 1
    uint32_t base;  // address of the first GDT entry
} __attribute__((packed));

struct gdt_entry gdt[3];
struct gdt_ptr gdt_descriptor;

extern void gdt_flush(uint32_t);

void gdt_set_entry(int num,
    uint32_t base,
    uint32_t limit,
    uint8_t access,
    uint8_t gran)
{
    gdt[num].base_low = (base & 0xFFFF); // first 16 bits
    gdt[num].base_middle = (base >> 16) & 0xFF; // next 8 bits
    gdt[num].base_high = (base >> 24) & 0xFF; // last 8 bits

    gdt[num].limit_low = (limit & 0xFFFF); // first 16 bits
    gdt[num].granularity = ((limit >> 16) & 0x0F); // last 4 bits

    gdt[num].granularity |= (gran & 0xF0); // granularity flags (4 bits)
    gdt[num].access = access; // access flags
}

void gdt_install()
{
    gdt_descriptor.limit = sizeof(gdt) - 1;
    gdt_descriptor.base = (uint32_t)&gdt;

    gdt_set_entry(0, 0, 0, 0, 0);                // null segment
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // code (flags = 1100) = granularity, 32bit
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // data (flags = 1100) = granularity, 32bit

    gdt_flush((uint32_t)&gdt_descriptor);
}

void gdt_enable_long_mode()
{
    gdt[1].granularity &= 0xBF; // disable 32-bit protected mode
    gdt[1].granularity |= 0x20; // enable 64-bit long mode
}
