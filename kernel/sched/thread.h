    //
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//


#ifndef UNTITLED_OS_THREADS_H
#define UNTITLED_OS_THREADS_H
#define MAXTHREADS 10
#include "../lib/include/stdint.h"
typedef size_ship pid_t;
enum cpu_state{
    NEW=0,
    RUNNABLE,
    ON_CPU,
    WAIT,
    EXIT
};
struct thread_ctx {
    pid_t pid;
    enum cpu_state state;
    int prio;
};

//struct thread_ctx all_threads[MAXTHREADS];

struct thread_ctx create_thread();
int exit_thread(int status);
struct thread_ctx get_thread_struct();
void passive_sleep();
#endif //UNTITLED_OS_THREADS_H
