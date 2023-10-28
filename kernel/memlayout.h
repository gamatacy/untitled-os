// Kernel starts at 0x100000 (1mb)
// And ends at symbol end

#define KSTART 0x100000
extern char end[]; // first address after kernel
                   // defined in linked.ld
#define KEND end