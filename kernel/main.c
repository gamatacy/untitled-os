//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//

#include "vga/vga.h"
#include "idt/idt.h"
#include "tty/tty.h"
#include "kalloc/kalloc.h"
#include "memlayout.h"
#include "lib/include/x86_64.h"
#include "paging/paging.h"
#include "sched/proc.h"
#include "sched/threads.h"
#include "sched/scheduler.h"



void print_num(uint32_t num) {
    while (1) {
        printf("Hello from thread %d\n", num);
        // yield();
    }
}
void thread_function(int argc, struct argument *args) {
    uint32_t num = *((uint32_t*) args[0].value);
    print_num(num);
}



int kernel_main(){
    init_tty();
    
    for (uint8_t i=0; i < TERMINALS_NUMBER; i++) {
        set_tty(i);
        printf("TTY %d\n", i);
    }
    set_tty(0);
    printf(
    " CR3: %x\n", rcr3()
    );

    print("$ \n");
    printf("Kernel end at address: %d\n", KEND);
    printf("Kernel size: %d\n", KEND - KSTART);

    kinit(KEND, INIT_PHYSTOP);
    pagetable_t kernel_table = kvminit(INIT_PHYSTOP, PHYSTOP);
    printf("kernel table: %p\n", kernel_table);
    kinit(INIT_PHYSTOP, PHYSTOP);
    printf("Successfully allocated physical memory up to %p\n", PHYSTOP);
    printf("%d pages available in allocator\n", count_pages());

    struct proc_node *init_proc_node = procinit();
    printf("Init proc node %p\n", init_proc_node);
    struct thread *init_thread = peek_thread_list(init_proc_node->data->threads);
    printf("Got init thread\n");

    setup_idt();

    //scheduler();

    while(1) {};
    return 0;
}