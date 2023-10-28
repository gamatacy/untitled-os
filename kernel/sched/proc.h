//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//


#ifndef UNTITLED_OS_PROC_H
#define UNTITLED_OS_PROC_H
#define MAXPROCS 10

#include "../lib/include/stdint.h"

typedef size_ship pid_t;

enum proc_state {
    NEW = 0,
    RUNNABLE,
    ON_CPU,
    WAIT,
    EXIT
};

struct proc {
    pid_t pid;
    enum proc_state state;
    struct proc *parent;
};

void passive_sleep();

int exit_proc(int status);

pid_t get_pid();

int exec(char *file, char *argv[]);

char *sbrk(int n);

struct proc init_first_proc();

struct proc fork();

struct proc forkexec();

#endif //UNTITLED_OS_PROC_H
