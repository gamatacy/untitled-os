//
// Created by oleg on 28.09.23.
//
#include "interrupt_handlers.h"
#include "../vga/vga.h"
#include "../tty/tty.h"

void divide_by_zero_handler(){
    print(&terminals[current_tty], "division by zero\n");
    while (1);
}