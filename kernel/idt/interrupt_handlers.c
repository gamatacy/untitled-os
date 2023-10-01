//
// Created by oleg on 28.09.23.
//
#include "interrupt_handlers.h"
#include "../vga/vga.h"
void divide_by_zero_handler(){
    print("division by zero\n");
    while (1);
}