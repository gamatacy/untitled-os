//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//


#ifndef UNTITLED_OS_THREADS_H
#define UNTITLED_OS_THREADS_H
#define MAXTHREADS 100

struct thread_ctx {
    unsigned long state;
    int prio;
};

struct thread_ctx all_threads[100];

struct proc create_thread();
int exit_thread();
struct proc get_thread_struct();
void passive_sleep();
#endif //UNTITLED_OS_THREADS_H
