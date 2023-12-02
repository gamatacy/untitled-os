//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//

#ifndef UNTITLED_OS_SPINLOCK_H
#define UNTITLED_OS_SPINLOCK_H
#include "../lib/include/stdint.h"
#include "../sched/proc.h"
#include "../lib/include/x86_64.h"

typedef struct {
    uship8 is_locked;
    char* name;
} spinlock;



#endif //UNTITLED_OS_SPINLOCK_H
