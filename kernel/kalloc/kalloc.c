#include "../kalloc/kalloc.h"
#include "../sync/spinlock.h"
#include "../memlayout.h"
#include "../lib/include/stdint.h"
#include "../tty/tty.h"

struct run {
  struct run *next;
};

struct {
//   struct spinlock lock;
  struct run *freelist;
} kmem;

void kinit() {
    // initlock(&kmem.lock, "kmem");
    char *p;
  p = (char*)PGROUNDUP((uint64_t)KEND);
  for(;p + PGSIZE <= PHYSTOP; p += PGSIZE)
    kfree(p);
}

void kfree(void *pa) {
    struct run *r;

  if(((uint64_t)pa % PGSIZE) != 0 || (char*)pa < end || (uint64_t)pa >= PHYSTOP)
    panic("kfree");

  // Fill with junk to catch dangling refs.
  char* testpa = (pa + PGSIZE -1);
  memset(pa, 1, PGSIZE);

  r = (struct run*)pa;

//   acquire(&kmem.lock);
  r->next = kmem.freelist;
  kmem.freelist = r;
//   release(&kmem.lock);
}

void *kalloc() {
    struct run *r;

//   acquire(&kmem.lock);
  r = kmem.freelist;
  if(r)
    kmem.freelist = r->next;
//   release(&kmem.lock);

  if(r)
    memset((char*)r, 5, PGSIZE); // fill with junk
  return (void*)r;
}