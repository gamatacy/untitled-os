#include "vga.h"

int kernel_main(){
    clear();
    set_bg(cyan);
    set_fg(white);
    print("Hello world!\nGoodbye world!\nChina-Russia os\n");
    while(1);
    return 0;
}