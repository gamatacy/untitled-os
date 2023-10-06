//
// Created by oleg on 30.09.23.
//

#ifndef UNTITLED_OS_TTY_H
#define UNTITLED_OS_TTY_H
#include "../vga/vga.h"
#include "../lib/include/stdint.h"
#define TERMINALS 12

struct tty {
    struct char_with_color tty_buffer[VGA_HEIGHT * VGA_WIDTH];
    uint8_t tty_id;
    uint8_t line;
    uint8_t pos;
};

extern uint8_t current_tty;
extern struct tty terminals[TERMINALS];

void init_tty();
void switch_tty(uint8_t tty_id);

#endif //UNTITLED_OS_TTY_H
