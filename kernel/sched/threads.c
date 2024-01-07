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

void init_thread_list(struct thread_list *list) {
    if (list == 0) {
        list = kalloc();
        list->head = 0;
        list->tail = 0;
    } else {
        //todo очистить список, если уже существует
        list->head = 0;
        list->tail = 0;
    }
}

void push_back_thread_list(struct thread_list *list, struct thread *thread) {
    struct thread_node *new_node = kalloc();
    new_node->data = thread;
    new_node->next = 0;
    if (list->tail != 0) {
        new_node->prev = list->tail;
        list->tail->next = new_node;
    } else {
        if (list->head != 0) {
            panic("unexpected error. Head of thread list can't be null");
        }
        new_node->prev = 0;
        list->head = new_node;
    }
    list->tail = new_node;
}

void push_front_thread_list(struct thread_list *list, struct thread *thread) {
    struct thread_node *new_node = kalloc();
    new_node->data = thread;
    new_node->prev = 0;
    if (list->head != 0) {
        new_node->next = list->head;
        list->head->prev = new_node;
    } else {
        if (list->tail != 0) {
            panic("unexpected error. Tail of thread list can't be null");
        }
        new_node->next = 0;
        list->tail = new_node;
    }
    list->head = new_node;
}

struct thread *pop_front_thread_list(struct thread_list *list) {
    struct thread *pop_thread;
    struct thread_node *pop_node;
    if (list->head == 0) {
        panic("Pop from empty thread list");
    }
    if (list->tail == 0) {
        panic("unexpected error. Tail of thread list can't be null(pop_front_thread_list)");
    }
    pop_node = list->head;
    pop_thread = pop_node->data;
    if (list->head == list->tail) {
        list->head = list->tail = 0;
    } else {
        list->head = list->head->next;
        list->head->prev = 0;
    }
    kfree(pop_node);
    return pop_thread;
}

struct thread *pop_back_thread_list(struct thread_list *list) {
    struct thread *pop_thread;
    struct thread_node *pop_node;
    if (list->head == 0) {
        panic("Pop from empty thread list");
    }
    if (list->tail == 0) {
        panic("unexpected error. Tail of thread list can't be null(pop_back_thread_list)");
    }
    pop_node = list->tail;
    pop_thread = pop_node->data;
    if (list->head == list->tail) {
        list->head = list->tail = 0;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = 0;
    }
    kfree(pop_node);
    return pop_thread;
}