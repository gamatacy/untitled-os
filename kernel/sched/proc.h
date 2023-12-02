//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//


#ifndef UNTITLED_OS_PROC_H
#define UNTITLED_OS_PROC_H
#define MAXPROCS 10

#include "../lib/include/stdint.h"
#include "../tty/tty.h"
typedef size_ship pid_t;



enum proc_state {
    NEW = 0,
    RUNNABLE,
    ON_CPU,
    WAIT,
    INTERRUPTIBLE,
    EXIT
};

struct proc {
    pid_t pid;
    enum proc_state state;
    struct proc *parent;
};


typedef struct {
    int ncli;                    // Depth of pushcli nesting.
    int intena;                  // Were interrupts enabled before pushcli?
    struct current_proc *proc;           // The process running on this cpu or null
} cpu;

cpu *current_cpu;


void set_proc_state(struct proc *const, enum proc_state);

void passive_sleep();

int exit_proc(int status);

pid_t get_pid();

int exec(char *file, char *argv[]);

char *sbrk(int n);

void panic(char *message);

struct proc init_first_proc();

struct proc fork();

struct proc forkexec();

#endif //UNTITLED_OS_PROC_H
