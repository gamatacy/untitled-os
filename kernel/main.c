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
//    procinit();

    uint32_t arg_value = 52;
    struct argument arg;
    arg.arg_size = 4;
    arg.value = &arg_value;
    struct thread *new_thread = create_thread(thread_function, 1, &arg);
    struct context kernel_context;
    struct context* kernel_context_ptr = &kernel_context;

    printf("Context address: %p\n", new_thread->context);
    printf("New thread return RIP: %p\n", *(uint64_t*)(new_thread->context + 1));
    printf("Thread function address: %p\n", thread_function);

    switch_context(&kernel_context_ptr, new_thread->context);
    while(1) {};
    return 0;
}