//
// Created by oleg on 30.09.23.
//

#include "tty.h"
#include "../lib/include/stdint.h"
#include "../lib/include/memset.h"
#define TERMINALS_NUMBER 7
static struct tty_structure tty_terminals[TERMINALS_NUMBER];
static struct tty_structure* active_tty;

int start_terminal(ship terminal){
    clear_vga();
    if(TERMINALS_NUMBER<=terminal){
        return 1;
    }
    return 0;
}

void init_tty(){
    memset(&tty_terminals, 0, sizeof(struct tty_structure) * TERMINALS_NUMBER);
    for (ship i = 0; i < TERMINALS_NUMBER; ++i) {
        (tty_terminals+i)->tty_id = i;
        (tty_terminals+i)->bg = DEFAULT_BG_COLOR;
        (tty_terminals+i)->fg = DEFAULT_FG_COLOR;
        (tty_terminals+i)->line = (tty_terminals+i)->pos = 0;
        memset((tty_terminals+i)->tty_buffer, 0, VGA_HEIGHT * VGA_WIDTH);
    }
};

void set_tty(ship terminal){
    if(TERMINALS_NUMBER<=terminal){
        return;
    }
    clear_vga();
}

void clear_current_tty(){
    memset(active_tty->tty_buffer, 0, active_tty->size);
    active_tty->pos = 0;
    active_tty->line = 0;
    clear_vga();
}