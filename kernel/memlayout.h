// Kernel starts at 0x100000 (1mb)
// And ends at symbol end
#define KSTART 0x100000
extern char end[]; // first address after kernel
                   // defined in linked.ld
#define KEND end

#define PHYSTOP 128*1024*1024           // Top physical memory

#define PGSIZE 4096 // bytes per page
#define PGSHIFT 12  // bits of offset within a page

#define PGROUNDUP(sz)  (((sz)+PGSIZE-1) & ~(PGSIZE-1))
#define PGROUNDDOWN(a) (((a)) & ~(PGSIZE-1))