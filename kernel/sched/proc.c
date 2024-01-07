//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//


#include "proc.h"

struct proc head;
struct proc *current_proc;
//pid_t current_pid = 1;
struct spinlock pid_lock;
struct spinlock proc_lock;

void procinit(void) {
    head.pid = -1;
    head.state = UNUSED;
    head.next = &head;
    head.prev = &head;
    initlock(&pid_lock, "pid_lock");
    initlock(&proc_lock, "proc_lock");
}

pid_t generate_pid() {
    acquire(&pid_lock);
    static pid_t current_pid = 1;
    int local_pid = current_pid;
    current_pid++;
    release(&pid_lock);
    return local_pid;
}

struct proc *allocproc(void) {
    struct proc *proc;
    proc = kalloc();
    proc->state = NEW;
    acquire(&proc_lock);
    proc->prev = &head;
    proc->next = head.next;
    head.next->prev = proc;
    head.next = proc;
    release(&proc_lock);
    proc->pid = generate_pid();
    proc->kstack = (uint64_t)
    kalloc();
}


void set_proc_state(struct proc *const proc, enum proc_state state) {
    proc->state = state;
}

//
//void passive_sleep() {
//
//}
//
int exit_proc(int status) {
    set_proc_state(current_proc, EXIT);
    //scheduler();
    return 0;
}

//
//pid_t get_pid() {
//    return current_proc->pid;
//}
//
//int exec(char *file, char *argv[]);
//
////Grow process’s memory by n bytes. Returns start of new memory
//char *sbrk(int n);
//
//struct proc init_first_proc() {
//    struct proc init_proc;
//    init_proc.parent = 0;
//    init_proc.pid = generate_pid();
//    set_proc_state(&init_proc, RUNNABLE);
//};
//
//struct proc fork() {
//    struct proc child_proc;
//    child_proc.pid = generate_pid();
//    child_proc.parent = current_proc;
//    set_proc_state(&child_proc, RUNNABLE);
//};
//
void panic(char *message) {
    print(message);
    print("\tpanic!");
    while (1) {}
}

struct proc forkexec();


void init_proc_list(struct proc_list *list) {
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

void push_back_proc_list(struct proc_list *list, struct proc *proc) {
    struct proc_node *new_node = kalloc();
    new_node->data = proc;
    new_node->next = 0;
    if (list->tail != 0) {
        list->tail->next = new_node;
    } else {
        list->head = list->tail = new_node;
    }
}

void push_front_proc_list(struct proc_list *list, struct proc *proc) {
    struct proc_node *new_node = kalloc();
    new_node->data = proc;
    new_node->next = 0;
    if (list->head != 0) {
        new_node->next = list->head;
    }
    else{
        list->tail = new_node;
    }
    list->head = new_node;
}

