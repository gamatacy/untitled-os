#include "vga/vga.h"
#include "idt/idt.h"
#include "tty/tty.h"

int kernel_main(){
    setup_idt();
    init_tty();

    for (uship8 i=0; i < TERMINALS; i++) {
        printf(i, "TTY %d\n", i);
    }
    print(current_tty, "$ \n");
    flush(current_tty);

    while(1);
    return 0;
}