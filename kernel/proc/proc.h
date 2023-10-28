//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//


#ifndef UNTITLED_OS_PROC_H
#define UNTITLED_OS_PROC_H
#define size_t pid_t
typedef struct proc_struct proc_struct
struct proc_struct{
    unsigned long state;
    int prio;
    unsigned long policy;
    struct proc *parent;
};

proc_struct createThread();
int exitThread();
proc_struct getThreadStruct();
void passiveSleep();
#endif //UNTITLED_OS_PROC_H
