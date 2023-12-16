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

int kernel_main(){
    setup_idt();
    init_tty();
    
    for (uship8 i=0; i < TERMINALS_NUMBER; i++) {
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

    kinit();
<<<<<<< HEAD
    // print_vm(rcr3());

    
    print_vm(init_tables());    
    
=======
    page_entry_raw res = walk(rcr3(), 3 << 12 << 27 + 2 << 12 << 18 + 1 << 12 << 9 + 0 << 12, 1);
    printf("Walk res: %p\n", res);
    //print_vm(rcr3());
>>>>>>> OlegSH

    while(1);
    return 0;
}