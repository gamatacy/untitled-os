//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//


#include "proc.h"
#include "../lib/include/panic.h"
#include "sched_states.h"

struct cpu current_cpu;
struct spinlock pid_lock;
struct spinlock proc_lock;
struct proc_node *proc_list;

pid_t generate_pid() {
    acquire(&pid_lock);
    static pid_t current_pid = 0;
    int local_pid = current_pid;
    current_pid++;
    release(&pid_lock);
    return local_pid;
}

struct proc *allocproc(void) {
    struct proc *proc = kalloc();

    if (proc == 0) {
        panic("Failed to alloc proc\n");
    }

    pid_t pid = generate_pid();
    
    for (int i = 0; i < NUMBER_OF_SCHED_STATES; i++) {
        proc->thread_states[i] = 0;
    }
    proc->killed = 0;
     

    acquire(&proc_lock);
    push_proc_list(&proc_list, proc);
    release(&proc_lock);

    return proc;
}

struct proc_node *procinit(void) {
    initlock(&pid_lock, "pid_lock");
    initlock(&proc_lock, "proc_lock");
    
    struct proc *init_proc = allocproc();
    
    static uint32_t arg_value = 52;
    static struct argument arg;
    arg.arg_size = sizeof(uint32_t);
    arg.value = &arg_value;
    struct thread *new_thread = create_thread(thread_function, 1, &arg);
    new_thread->state = RUNNABLE;
    new_thread->proc = init_proc;

    push_thread_list(init_proc->thread_states + RUNNABLE, new_thread);
}

void push_proc_list(struct proc_node **list, struct proc *proc) {
    struct proc_node *new_node = kalloc();
    new_node->data = proc;
    if ((*list) != 0) {
        new_node->next = (*list);
        new_node->prev = (*list)->prev;
        (*list)->prev->next = new_node;
        (*list)->prev = new_node;
    } else {
        new_node->prev = new_node;
        new_node->next = new_node;
        *list = new_node;
    }
}

struct proc *pop_proc_list(struct proc_node **list) {
    if (*list == 0) {
        panic("Empty proc list while popping\n");
    } else {
        struct proc* p = (*list)->data;
        if ((*list)->next = (*list)) {
            kfree(*list);
            *list = 0;
        } else {
            (*list)->prev->next = (*list)->next;
            (*list)->next->prev = (*list)->prev;
            kfree(*list);
        }
        return p;
    }
}

void shift_proc_list(struct proc_node **list) {
    if (*list == 0) {
        panic("Empty proc list while shifting\n");
    } else {
        *list = (*list)->next;
    }
}

struct proc *peek_proc_list(struct proc_node **list) {
    if (*list == 0) {
        panic("Empty proc list while peeking\n");
    } else {
        return (*list)->data;
    }
}

