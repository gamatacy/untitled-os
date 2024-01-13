//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//

#include "scheduler.h"
#include "proc.h"
#include "threads.h"
#include "../lib/include/panic.h"

uint32_t current_proc_rounds = 0;

struct thread *get_next_thread() {
    if (proc_list == 0) panic("schedule: no procs");
    struct proc *first_proc = peek_proc_list(proc_list);
    struct proc *current_proc;

    if (current_proc_rounds >= ROUNDS_PER_PROC) {
        current_proc_rounds = 0;
        shift_proc_list(&proc_list);
    }

    do {
        current_proc = peek_proc_list(proc_list);

        // If proc has threads
        if (current_proc->threads != 0) panic("schedule: proc with no threads\n");

        struct thread *first_thread = peek_thread_list(current_proc->threads);
        struct thread *current_thread;

        do {
            current_thread = peek_thread_list(current_proc->threads);
            shift_thread_list(current_proc->threads);
            if (current_thread->state == RUNNABLE) {
                return current_thread;
            }
        } while (peek_thread_list(current_proc->threads) != first_thread);

        current_proc_rounds = 0;
        shift_proc_list(proc_list);
    } while (peek_proc_list(proc_list) != first_proc);

    panic("shcedule: no available threads\n");
}