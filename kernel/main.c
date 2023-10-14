#include "vga/vga.h"
#include "idt/idt.h"
#include "tty/tty.h"

int kernel_main(){
    setup_idt();
    init_tty();
    for (uship8 i=0; i < TERMINALS_NUMBER; i++) {
        set_tty(i);
        printf("TTY %d\n", i);
    }
    set_tty(0);
    print("$ \n");
    while(1);
    return 0;
}