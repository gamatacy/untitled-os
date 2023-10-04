#include "vga/vga.h"
#include "idt/idt.h"
int kernel_main(){
    setup_idt();
    clear();
    print("$ \n");
    
    while(1) {      
        asm ("hlt");
    }

    return 0;
}   