#define uint32_t unsigned int
#define uint64_t unsigned long long

uint64_t pml4[512] __attribute__((aligned(4096)));
uint64_t pdpt[512] __attribute__((aligned(4096)));
uint64_t pd[512] __attribute__((aligned(4096)));

void setup_paging()
{
    pml4[0] = (uint64_t)&pdpt | 3;
    pdpt[0] = (uint64_t)&pd | 3;
    pd[0] = 0x000000 | 0x83;
    pd[1] = 0x200000 | 0x83;
}
