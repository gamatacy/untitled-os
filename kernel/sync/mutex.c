//
// Created by ShipOS developers on 03.01.24.
// Copyright (c) 2024 SHIPOS. All rights reserved.
//

#include "mutex.h"

int init_mutex(struct mutex *lk, char *name) {
    lk->spinlock = 0;
    lk->thread_node = 0;
    init_spinlock(lk->spinlock, name);
}

void acquire_mutex(struct mutex *lk) {
    if (lk == 0) {
        panic("panic in acquire_mutex");
    }
    int bool = holding_spinlock(lk->spinlock);
    if (bool == 0) {
        lk->spinlock->is_locked = 1;
        return;
    } else {
        push_thread_list(&lk->thread_list, current_cpu.thread);
    }
};

void release_mutex(struct mutex *lk) {

}

