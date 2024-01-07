//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//


#ifndef UNTITLED_OS_PROC_H
#define UNTITLED_OS_PROC_H
#define MAXPROCS 100
//#include "../lib/include/stdint.h"
#include <inttypes.h>
#include <stddef.h>
#include "../tty/tty.h"
#include "../sync/spinlock.h"
#include "../../kernel/kalloc/kalloc.h"
#include "scheduler.h"
typedef size_t pid_t;


struct proc {
    pid_t pid;
    enum sched_states state;
    int killed;
    int xstate;
    uint64_t kstack;
    struct proc *prev;
    struct proc *next;
};

struct cpu {
    int ncli;                    // Depth of pushcli nesting.
    int intena;                  // Were interrupts enabled before pushcli?
    struct current_proc *proc;           // The process running on this cpu or null
};

struct proc_node {
    struct proc *data;
    struct proc_node *next;
    struct proc_node *prev;
};

struct proc_list {
    struct proc_node *head;
    struct proc_node *tail;
};

struct cpu current_cpu;

void init_proc_list(struct proc_list *list);

void push_back_proc_list(struct proc_list *list, struct proc *proc);

void push_front_proc_list(struct proc_list *list, struct proc *proc);

struct proc* pop_front_proc_list(struct proc_list *list);

struct proc *pop_back_proc_list(struct proc_list *list);


void procinit(void);

void set_proc_state(struct proc *const, enum sched_states);

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
