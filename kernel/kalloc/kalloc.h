#ifndef KALLOC_H
#define KALLOC_H

#include "../lib/include/stdint.h"

void kinit(uint64_t, uint64_t);
void *kalloc(void);
void kfree(void*);

#endif