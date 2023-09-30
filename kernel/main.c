#include "lib/include/print.h"
#include "idt/idt.h"
int kernel_main(){
    clear();
    setup_idt();
    set_bg(cyan);
    set_fg(white);
    print("Hello world!\nGoodbye world!\nChina-Russia os\n");
    // int x = 10/0;
    while(1);
    return 0;
}