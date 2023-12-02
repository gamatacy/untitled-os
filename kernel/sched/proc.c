//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//


#include "proc.h"
struct proc *current_proc;
//cpu *current_cpu;

pid_t generate_pid() {
    static pid_t pid = 0;
    return pid++;
}

void set_proc_state(struct proc *const proc, enum proc_state state) {
    proc->state = state;
}

void passive_sleep() {

}

int exit_proc(int status) {
    set_proc_state(current_proc, EXIT);
    //scheduler();
    return 0;
}

pid_t get_pid() {
    return current_proc->pid;
}

int exec(char *file, char *argv[]);

//Grow process’s memory by n bytes. Returns start of new memory
char *sbrk(int n);

struct proc init_first_proc() {
    struct proc init_proc;
    init_proc.parent = 0;
    init_proc.pid = generate_pid();
    set_proc_state(&init_proc, RUNNABLE);
};

struct proc fork() {
    struct proc child_proc;
    child_proc.pid = generate_pid();
    child_proc.parent = current_proc;
    set_proc_state(&child_proc, RUNNABLE);
};

void panic(char *message) {
    print(message);
    exit_proc(1);
}

struct proc forkexec();
