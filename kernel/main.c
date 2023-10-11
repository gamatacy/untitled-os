#include "vga/vga.h"
#include "idt/idt.h"
#include "tty/tty.h"
#include "paging/paging.h"

int kernel_main(){

    setup_idt();
    init_tty();

    print("INITIALIZING PAGING");
    init_paging();
    print("PAGING INITIALIZED");

    for (uship8 i=0; i < TERMINALS_NUMBER; i++) {
        printf("TTY %d\n", i);
    }
    print("$ \n");
    while(1);
    return 0;
}