#include "vga/vga.h"
#include "idt/idt.h"
int kernel_main(){
    setup_idt();
    clear();
    print("$ \n");
    // int x = 10/0;
    while(1);
    return 0;
}