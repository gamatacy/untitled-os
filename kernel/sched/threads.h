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
  //  struct thr_node *item;
    struct context *context;
    void (*start_function)(void *);
    uint64_t stack;
    uint64_t kstack;
    size_t argc;
    struct argument *args;
    enum sched_states state;
};

struct thr_node {
    struct thread *data;
    struct thr_node *next;
    struct thr_node *prev;
};

struct looped_thrlist {
    struct thr_node *head;
    struct thr_node *tail;
};

void init_thread_list(struct looped_thrlist *list);

struct looped_thrlist* get_thrlist_state(enum sched_states state);

void push_back_thread_list(struct looped_thrlist *list, struct thread *thread);

void push_front_thread_list(struct looped_thrlist *list, struct thread *thread);

struct thread *pop_front_thread_list(struct looped_thrlist *list);

struct thread *pop_back_thread_list(struct looped_thrlist *list);

struct thread *create_thread(void (*start_function)(void *), int argc, struct argument *args);

void thread_function(int argc, struct argument *args);

void set_thread_state(struct thread *const, enum sched_states);

#endif //UNTITLED_OS_THREADS_H
