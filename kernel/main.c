#include "lib/vga.h"
#include "idt/idt.h"
int kernel_main(){
    setup_idt();
    clear();
    set_bg(cyan);
    set_fg(white);
    print("Hello world!\nGoodbye world!\nChina-Russia os\n");
    while(1);
    return 0;
}