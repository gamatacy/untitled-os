//
// Created by ShipOS developers on 20.12.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//

#include "threads.h"
#include <ucontext.h>

struct thread *current_thread = 0;

void thread_function(void *args) {
    print("Thread started\n");
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
    thread->start_function = start_function;
    thread->argc = argc;
    thread->args = args;
    void *sp = thread->stack;
//    makecontext(&thread->context, start_function, 1, args);
}

struct thread *create_thread(void (*start_function)(void *), void *args) {
    struct thread *new_thread = (struct thread *) kalloc();
    init_thread(new_thread, start_function, args);
    return new_thread;
}