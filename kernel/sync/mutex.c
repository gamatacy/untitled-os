//
// Created by ShipOS developers on 03.01.24.
// Copyright (c) 2024 SHIPOS. All rights reserved.
//

#include "mutex.h"

int init_mutex(struct mutex *lk, char *name) {
    lk->spinlock = kalloc();
    lk->thread_list = 0;
    init_spinlock(lk->spinlock, name);
}

void acquire_mutex(struct mutex *lk) {
    if (lk == 0) {
        panic("panic in acquire_mutex");
    }
    check_mutex:
    int bool = holding_spinlock(lk->spinlock);
    if (bool == 0) {
        acquire_spinlock(lk->spinlock);
        return;
    } else {
        push_thread_list(&lk->thread_list, current_cpu.current_thread);
        change_thread_state(current_cpu.current_thread, WAIT);
        //todo scheduler
        goto check_mutex;
    }
};

void release_mutex(struct mutex *lk) {
    if (lk->spinlock->is_locked != 0) {
        panic("release_mutex");
    }
    if (lk->thread_list == 0) {
        release_spinlock(lk->spinlock);
        return;
    } else {
        struct thread *thread = pop_thread_list(&lk->thread_list);
        change_thread_state(thread, RUNNABLE);
        //todo scheduler
    }
}

void destroy_mutex(struct mutex *lk) {
    kfree(lk);
}