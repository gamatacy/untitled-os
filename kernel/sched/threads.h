//
// Created by ShipOS developers on 20.12.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//

#ifndef UNTITLED_OS_THREADS_H
#define UNTITLED_OS_THREADS_H

#include "../memlayout.h"
#include "../kalloc/kalloc.h"
#include "../lib/include/x86_64.h"
#include <stddef.h>
#include <inttypes.h>
#include "../lib/include/memset.h"
#define NUMBER_OF_SCHED_STATES 6

enum sched_states {
    NEW = 0,
    RUNNABLE,
    ON_CPU,
    WAIT,
    EXIT,
    UNUSED
};

struct argument {
    char *value;
    size_t arg_size;
};

struct thread {
    struct context *context;
    void (*start_function)(void *);
    uint64_t stack;
    uint64_t kstack;
    size_t argc;
    struct argument *args;
    enum sched_states state;
};

struct thread_node {
    struct thread *data;
    struct thread_node *next;
    struct thread_node *prev;
};

void push_thread_list(struct thread_node **list, struct thread *thread);

struct thread *pop_thread_list(struct thread_node **list);

void shift_thread_list(struct thread_node **list);

struct thread *peek_thread_list(struct thread_node **list);

struct thread *create_thread(void (*start_function)(void *), int argc, struct argument *args);

void thread_function(int argc, struct argument *args);

#endif //UNTITLED_OS_THREADS_H
