//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//


#include "thread.h"

pid_t pid = 0;
void init_threads(){
    for (int i = 0; i < MAXTHREADS; ++i) {
        struct thread_ctx new_thread;
        new_thread.state = NEW;
    }
}
pid_t generate_pid(){
    return pid++;
}
struct thread_ctx create_thread(){
    struct thread_ctx new_thread;
    new_thread.pid = generate_pid();
    new_thread.state = RUNNABLE;
    //all_threads[pid] = new_thread;
    return new_thread;
}
//int exit_thread(){
//
//};
//struct proc get_thread_struct(){
//    return 0;
//};
void passive_sleep(){

};