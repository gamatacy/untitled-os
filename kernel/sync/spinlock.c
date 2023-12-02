//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//

#include "spinlock.h"

void initlock(spinlock* lock, char* name){
    lock->name = name;
    lock->is_locked = 0;
}

