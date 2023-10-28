//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//


#ifndef UNTITLED_OS_THREADS_H
#define UNTITLED_OS_THREADS_H
#define MAXTHREADS 100

struct threadCtx all_threads[100];

struct threadCtx {
    unsigned long state;
    int prio;
};

struct proc createThread();
int exitThread();
struct proc getThreadStruct();
void passiveSleep();
#endif //UNTITLED_OS_THREADS_H
