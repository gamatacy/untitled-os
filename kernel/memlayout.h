// Kernel starts at 0x100000 (1mb)
// And ends at symbol end

#define KSTART 0x100000
#define PHYSTOP 0xE000000           // Top physical memory
#define DEVSPACE 0xFE000000         // Other devices are at high addresses
#define KERNBASE 0x80000000         // First kernel virtual address
#define KERNLINK (KERNBASE+KSTART)  // Address where kernel is linked

#define V2P(a) (((uint) (a)) - KERNBASE)
#define P2V(a) ((void *)(((char *) (a)) + KERNBASE))

#define V2P_WO(x) ((x) - KERNBASE)    // same as V2P, but without casts
#define P2V_WO(x) ((x) + KERNBASE)    // same as P2V, but without casts

extern char end[]; // first address after kernel
                   // defined in linked.ld
#define KEND end