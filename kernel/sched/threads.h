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

struct argument{
    void* arg_adr;
    size_t arg_size;
};

struct thread {
    struct context context;
    void (*start_function)(void *);
    uint64_t stack;
    uint64_t kstack;
    size_t argc;
    struct argument *args;
};

void init_thread(struct thread *thread, void (*start_function)(void *), void *args);

struct thread *create_thread(void (*start_function)(void *), void *args);

void thread_function(void *args);

#endif //UNTITLED_OS_THREADS_H
