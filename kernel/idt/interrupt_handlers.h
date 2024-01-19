//
// Created by oleg on 28.09.23.
//

#ifndef UNTITLED_OS_INTERRUPT_HANDLERS_H
#define UNTITLED_OS_INTERRUPT_HANDLERS_H
//#include "../lib/include/stdint.h"
#include <inttypes.h>
#include "../lib/include/x86_64.h"
void keyboard_handler_wrapper();
void keyboard_handler();
void timer_interrupt();
void default_handler();
void interrupt_handler(uint64_t, uint64_t);

void interrupt_handler_0();
void interrupt_handler_1();
void interrupt_handler_2();
void interrupt_handler_3();
void interrupt_handler_4();
void interrupt_handler_5();
void interrupt_handler_6();
void interrupt_handler_7();
void interrupt_handler_8();
void interrupt_handler_9();
void interrupt_handler_10();
void interrupt_handler_11();
void interrupt_handler_12();
void interrupt_handler_13();
void interrupt_handler_14();
void interrupt_handler_15();
void interrupt_handler_16();
void interrupt_handler_17();
void interrupt_handler_18();
void interrupt_handler_19();
void interrupt_handler_20();
void interrupt_handler_21();
void interrupt_handler_22();
void interrupt_handler_23();
void interrupt_handler_24();
void interrupt_handler_25();
void interrupt_handler_26();
void interrupt_handler_27();
void interrupt_handler_28();
void interrupt_handler_29();
void interrupt_handler_30();
void interrupt_handler_31();

#endif //UNTITLED_OS_INTERRUPT_HANDLERS_H
