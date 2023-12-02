#include "../kalloc/kalloc.h"
#include "../buddy_alloc/buddy.h"
#include "../memlayout.h"
#include "../lib/include/stdint.h"

void kinit() {
    char* start = (char *) PGROUNDUP((uint64_t)KEND);
    bd_init(start, PHYSTOP);
}

void *kalloc() {
    return bd_malloc();
}

void kfree(void* pa) {
    bd_free(pa);
}