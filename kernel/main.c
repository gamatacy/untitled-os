//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//

#include "vga/vga.h"
#include "idt/idt.h"
#include "tty/tty.h"
#include "kalloc/kalloc.h"
#include "buddy_alloc/buddy.h"
#include "memlayout.h"

int kernel_main(){
    setup_idt();
    init_tty();
    
    for (uship8 i=0; i < TERMINALS_NUMBER; i++) {
        set_tty(i);
        printf("TTY %d\n", i);
    }
    set_tty(0);
    print("$ \n");
    printf("Kernel end at address: %d\n", KEND);
    printf("Kernel size: %d\n", KEND - KSTART);

    //kinit();
    //bd_print();

    while(1);
    return 0;
}