//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//


#ifndef UNTITLED_OS_PROC_H
#define UNTITLED_OS_PROC_H
#define size_t pid_t
#include "../threads/thread.h"

struct proc{
    unsigned long policy;
    struct proc *parent;
    struct threadCtx *threads;
};


#endif //UNTITLED_OS_PROC_H