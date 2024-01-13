//
// Created by ShipOS developers on 20.12.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//

#include "threads.h"

struct looped_thrlist *thread_states[NUMBER_OF_SCHED_STATES];

struct thread *current_thread = 0;

void thread_function(int argc, struct argument *args) {
    uint32_t num = *((uint32_t*) args[0].value);
    print_num(num);
}

void print_num(uint32_t num) {
    printf("Thread started with arg %d\n", num);
    while (1) {}
}

void init_thread_states() {
    for (int i = 0; i < NUMBER_OF_SCHED_STATES; ++i) {
        init_thread_list(thread_states[i]);
    }
}

struct looped_thrlist *get_thrlist_state(enum sched_states state) {
    return thread_states[state];
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
    sp -= sizeof(uint64_t);     
    *(uint64_t * )(sp) = start_function;
    sp -= sizeof(struct context) - sizeof(uint64_t);
    memset(sp, 0, sizeof(struct context) - sizeof(uint64_t));
    thread->context = (struct context *) sp;
    thread->context->rdi = argc;
    thread->context->rsi = args;
}

struct thread *create_thread(void (*start_function)(void *), int argc, struct argument *args) {
    struct thread *new_thread = (struct thread *) kalloc();
    init_thread(new_thread, start_function, argc, args);
    return new_thread;
}

void set_thread_state(struct thread *const thread, enum sched_states state) {
    //todo удалить нужный thread из списка
    thread->state = state;
    push_back_thread_list(thread_states[state], thread);
}

void init_thread_list(struct looped_thrlist *list) {
    if (list == 0) {
        list = kalloc();
        list->head = 0;
        list->tail = 0;
    } else {
        while (list->head != 0) {
            pop_back_thread_list(list);
        }
        list->head = 0;
        list->tail = 0;
    }
}

void push_back_thread_list(struct looped_thrlist *list, struct thread *thread) {
    struct thr_node *new_node = kalloc();
    new_node->data = thread;
    new_node->next = list->head;
    if (list->tail != 0) {
        list->head->prev = new_node;
        list->tail->next = new_node;
        new_node->prev = list->tail;
    } else {
        if (list->head != 0) {
            panic("unexpected error. Head of thread list can't be null");
        }
        new_node->prev = list->head;
        list->head = new_node;
    }
    list->tail = new_node;
}

void push_front_thread_list(struct looped_thrlist *list, struct thread *thread) {
    struct thr_node *new_node = kalloc();
    new_node->data = thread;
    new_node->prev = list->tail;
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

struct thread *pop_front_thread_list(struct looped_thrlist *list) {
    struct thread *pop_thread;
    struct thr_node *pop_node;
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

struct thread *pop_back_thread_list(struct looped_thrlist *list) {
    struct thread *pop_thread;
    struct thr_node *pop_node;
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