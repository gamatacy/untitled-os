//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//

#include "spinlock.h"
#include "../lib/include/x86_64.h"
// Eflags register
#define FL_INT           0x00000200      // Interrupt Enable

void initlock(spinlock *lock, char *name) {
    lock->is_locked = 0;
    lock->name = name;
}

void acquire(spinlock *lk) {
    pushcli(); // disable interrupts to avoid deadlock.
    if (holding(lk))
        panic("acquire");

    // The xchg is atomic.
    while (xchg(&lk->is_locked, 1) != 0);

    // Tell the C compiler and the processor to not move loads or stores
    // past this point, to ensure that the critical section's memory
    // references happen after the lock is acquired.
    __sync_synchronize();

}

void release(spinlock *lk) {
    if (!holding(lk))
        panic("release");

    // Tell the C compiler and the processor to not move loads or stores
    // past this point, to ensure that all the stores in the critical
    // section are visible to other cores before the lock is released.
    // Both the C compiler and the hardware may re-order loads and
    // stores; __sync_synchronize() tells them both not to.
    __sync_synchronize();

    // Release the lock, equivalent to lk->locked = 0.
    // This code can't use a C assignment, since it might
    // not be atomic. A real OS would use C atomics here.
    asm volatile("movl $0, %0" : "+m" (lk->is_locked) : );

    popcli();
}

int
holding(spinlock *lock) {
    int r;
    pushcli();
    r = lock->is_locked;
    popcli();
    return r;
}

void pushcli(void) {
    int eflags;

    eflags = readeflags();
    cli();
    if (current_cpu->ncli == 0)
        current_cpu->intena = eflags & FL_INT;
    current_cpu->ncli += 1;
}

void popcli(void) {
    if (readeflags() & FL_INT)
        panic("popcli - interruptible");
    if (--current_cpu->ncli < 0)
        panic("popcli");
    if (current_cpu->ncli == 0 && current_cpu->intena)
        sti();
}