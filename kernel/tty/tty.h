//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//

#ifndef UNTITLED_OS_TTY_H
#define UNTITLED_OS_TTY_H
#include "../vga/vga.h"
#include <inttypes.h>
#define TERMINALS_NUMBER 7
typedef struct {
    struct char_with_color tty_buffer[VGA_HEIGHT * VGA_WIDTH];
    uint8_t tty_id;
    uint8_t line;
    uint8_t pos;
    enum vga_colors bg;
    enum vga_colors fg;
} tty_structure;


void init_tty();
void set_tty(uint8_t terminal);
void set_fg(enum vga_colors fg);
void set_bg(enum vga_colors bg);
void itoa(int num, char* str, int radix);
void print(const char *string);
void printf(const char* format, ...);
void clear_current_tty();
uint8_t get_current_tty();
#endif //UNTITLED_OS_TTY_H
