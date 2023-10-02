#include "lib/include/print.h"
#include "idt/idt.h"
int kernel_main(){
    clear();
    setup_idt();
    set_bg(cyan);
    set_fg(white);
    print("Hello world!\nGoodbye world!\nChina-Russia os\n");
    uint64_t big_num = 1<<63 - 1;
    printf("%b\n", big_num);
    // int x = 10/0;
    for (;;)
        asm("hlt");
}