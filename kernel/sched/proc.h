//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//


#ifndef UNTITLED_OS_PROC_H
#define UNTITLED_OS_PROC_H

#include "thread.h"


struct proc{
    struct proc *parent;
    struct threadCtx *threads;
};
struct proc init_first_proc();
struct proc fork();

#endif //UNTITLED_OS_PROC_H
