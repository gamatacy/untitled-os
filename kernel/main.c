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
int kernel_main(){
    setup_idt();
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
    struct thread *init_thread = peek_thread_list(init_proc_node->data->thread_states[RUNNABLE]);
    struct context kernel_context;
    struct context *kernel_context_ptr = &kernel_context;

    switch_context(&kernel_context_ptr, init_thread->context);

    while(1) {};
    return 0;
}