//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//

#ifndef UNTITLED_OS_SHEDULER_H
#define UNTITLED_OS_SHEDULER_H

#include "threads.h"

#define NUMBER_OF_SCHED_STATES 7

enum sched_states {
    NEW = 0,
    RUNNABLE,
    ON_CPU,
    WAIT,
    INTERRUPTIBLE,
    EXIT,
    UNUSED
};

void thread_scheduler();

#endif //UNTITLED_OS_SHEDULER_H
