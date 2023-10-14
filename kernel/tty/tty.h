//
// Created by oleg on 30.09.23.
//

#ifndef UNTITLED_OS_TTY_H
#define UNTITLED_OS_TTY_H
#include "../vga/vga.h"
#include "../lib/include/stdint.h"
#define TERMINALS_NUMBER 7
struct tty_structure{
    struct char_with_color tty_buffer[VGA_HEIGHT * VGA_WIDTH];
    uship8 tty_id;
    uint8_t line;
    uint8_t pos;
    enum vga_colors bg;
    enum vga_colors fg;
};


void init_tty();
void set_tty(uship8 terminal);
void set_fg(enum vga_colors fg);
void set_bg(enum vga_colors bg);
void itoa(ship num, char* str, ship radix);
void print(const char *string);
void printf(const char* format, ...);
void clear_current_tty();
uship8 get_current_tty();
#endif //UNTITLED_OS_TTY_H
