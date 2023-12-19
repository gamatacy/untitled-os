//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//

#ifndef UNTITLED_OS_SPINLOCK_H
#define UNTITLED_OS_SPINLOCK_H

#include "../lib/include/stdint.h"
#include "../sched/proc.h"
#include "../lib/include/x86_64.h"
//#include "../../kernel/sched/proc.h"

struct spinlock {
    uint8_t is_locked;
    char *name;
};

void initlock(struct spinlock *lock, char *name);
void acquire(struct spinlock *lk);
void release(struct spinlock *lk);
int holding(struct spinlock *lock);

#endif //UNTITLED_OS_SPINLOCK_H
