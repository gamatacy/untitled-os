//
// Created by oleg on 30.09.23.
//

#ifndef UNTITLED_OS_TTY_H
#define UNTITLED_OS_TTY_H
#include "../vga/vga.h"
#include "../lib/include/stdint.h"
struct tty_structure{
    struct char_with_color tty_buffer[VGA_HEIGHT * VGA_WIDTH];
    ship8 tty_id;
    size_ship size;
    uint8_t line;
    uint8_t pos;
    enum vga_colors bg;
    enum vga_colors fg;
};

void init_tty();
void set_tty(ship terminal);

#endif //UNTITLED_OS_TTY_H
