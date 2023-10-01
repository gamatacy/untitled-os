#include "lib/include/vga.h"
#include "idt/idt.h"
int kernel_main(){
    setup_idt();
    clear();
    set_bg(cyan);
    set_fg(white);
    print("$ \n");
    while(1);
    return 0;
}