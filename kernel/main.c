#include "vga/vga.h"
#include "idt/idt.h"
int kernel_main(){
    setup_idt();
    clear_vga();
    print("$ \t");
    while(1);
    return 0;
}