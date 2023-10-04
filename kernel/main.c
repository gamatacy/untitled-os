#include "vga/vga.h"
#include "idt/idt.h"
#include "tty/tty.h"

int kernel_main(){
    setup_idt();
    init_tty();
    
    for (uint8_t i=0; i < TERMINALS; i++) {
        printf(i, "TTY %d", i);
    }
    print(current_tty, "$ \n");

    while(1);
    return 0;
}