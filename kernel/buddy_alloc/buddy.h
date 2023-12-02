#ifndef BUDDY_H
#define BUDDY_H

void bd_init(void* base, void* end);
void bd_free(void*);
void *bd_malloc(void);
void bd_print();

#endif // BUDDY_H