//
// Created by ShipOS developers on 20.12.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//

#include "threads.h"
#include <ucontext.h>

struct thread *current_thread = 0;

void thread_function(uint32_t num) {
    printf("Thread started with arg %d\n", num);
    while (1) {
//        printf("Thread is running\n");
//        yield();
    }
}

void init_thread(struct thread *thread, void (*start_function)(void *), int argc, struct argument *args) {
    thread->stack = kalloc();
    thread->kstack = kalloc();
    memset(thread->stack, 0, PGSIZE);
    memset(thread->kstack, 0, PGSIZE);
    thread->kstack += PGSIZE;
    thread->stack += PGSIZE;
    thread->start_function = start_function;
    thread->argc = argc;
    thread->args = args;
    char *sp = thread->stack;
    for (int i = argc - 1; i >= 0; i--) {
        for (int j = args[i].arg_size - 1; j >= 0; j--) {
            *(--sp) = args->value[j];
        }
    }

    sp -= sizeof(uint64_t);
    *(uint64_t*)(sp) = start_function;
    sp -= sizeof(struct context) - sizeof(uint64_t);
    memset(sp, 0, sizeof(struct context)- sizeof(uint64_t));
    thread->context = (struct context*)sp;
}

struct thread *create_thread(void (*start_function)(void *), int argc, struct argument *args) {
    struct thread *new_thread = (struct thread *) kalloc();
    init_thread(new_thread, start_function, argc, args);
    return new_thread;
}