//
// Created by oleg on 28.09.23.
//

#ifndef UNTITLED_OS_INTERRUPT_HANDLERS_H
#define UNTITLED_OS_INTERRUPT_HANDLERS_H
#include "../lib/include/stdint.h"

void divide_by_zero_handler();
void keyboard_handler_wrapper();
void keyboard_handler();
void timer_interrupt();
void default_handler();
void interrupt_handler(uint64_t, uint64_t);
void interrupt_handler_14();

#endif //UNTITLED_OS_INTERRUPT_HANDLERS_H
