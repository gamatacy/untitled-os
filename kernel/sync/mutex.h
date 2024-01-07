//
// Created by ShipOS developers on 03.01.24.
// Copyright (c) 2024 SHIPOS. All rights reserved.
//

#ifndef UNTITLED_OS_MUTEX_H
#define UNTITLED_OS_MUTEX_H

#include "spinlock.h"

struct mutex {
    struct spinlock spinlock;
    struct proc_list list;
};

void init_mutex(struct spinlock *lock, char *name);

void acquire_mutex(struct mutex *lk);

void release_mutex(struct mutex *lk);


#endif //UNTITLED_OS_MUTEX_H
