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
#include "scheduler.h"

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

struct thread_list {
    struct thread_node *head;
    struct thread_node *tail;
};

void init_thread_list(struct thread_list *list);

void push_back_thread_list(struct thread_list *list, struct thread *thread);

void push_front_thread_list(struct thread_list *list, struct thread *thread);

struct thread *pop_front_thread_list(struct thread_list *list);

struct thread *pop_back_thread_list(struct thread_list *list);

struct thread *create_thread(void (*start_function)(void *), int argc, struct argument *args);

void thread_function(uint32_t);

#endif //UNTITLED_OS_THREADS_H
