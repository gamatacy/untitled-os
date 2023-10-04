//
// Created by oleg on 30.09.23.
//

#include "tty.h"
#include "../lib/include/memset.h"

uship8 current_tty = 0;

void init_tty() {
    for (uint8_t i=0; i<TERMINALS; i++) {
        memset(terminals[i].tty_buffer, 0, sizeof(terminals[i].tty_buffer));
        terminals[i].line = 0;
        terminals[i].pos = 0;
        terminals[i].tty_id = i;
    }
    current_tty = 0;
}

void switch_tty(uint8_t tty_id) {
    flush(&terminals[tty_id]);
    current_tty = tty_id;
}