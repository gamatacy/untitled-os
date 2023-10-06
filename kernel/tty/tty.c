
#include "tty.h"
#include "../lib/include/stdint.h"
#include "../lib/include/memset.h"
#define TERMINALS_NUMBER 7
static struct tty_structure tty_terminals[TERMINALS_NUMBER];
static struct tty_structure* active_tty;

void init_tty(){
    memset(&tty_terminals, 0, sizeof(struct tty_structure) * TERMINALS_NUMBER);
    for (ship i = 0; i < TERMINALS_NUMBER; ++i) {
        (tty_terminals+i)->tty_id = i;
        (tty_terminals+i)->size = 0;
        (tty_terminals+i)->bg = DEFAULT_BG_COLOR;
        (tty_terminals+i)->fg = DEFAULT_FG_COLOR;
        (tty_terminals+i)->line = (tty_terminals+i)->pos = 0;
        memset((tty_terminals+i)->tty_buffer, 0, VGA_HEIGHT * VGA_WIDTH);
    }
    set_tty(0);
};

void set_tty(uship8 terminal){
    if(TERMINALS_NUMBER<=terminal){
        return;
    }
    clear_vga();
    active_tty = tty_terminals+terminal;
    write_buffer(active_tty->tty_buffer);
}

void clear_current_tty(){
    memset(active_tty->tty_buffer, 0, VGA_WIDTH*VGA_HEIGHT);
    active_tty->pos = 0;
    active_tty->line = 0;
    clear_vga();
}
uship8 get_current_tty(){
    return active_tty->tty_id;
}