//
// Created by oleg on 28.09.23.
//

#ifndef UNTITLED_OS_IDT_H
#define UNTITLED_OS_IDT_H

#include "../lib/include/stdint.h"
#define NUM_IDT_ENTRIES 256

struct IDTR {
    uship16 limit;           // IDT size
    uship64 base;            // IDT pointer
} __attribute__((packed));

struct InterruptDescriptor64 {
    uship16 offset_1;        // offset bits 0..15
    uship16 selector;        // a code segment selector in GDT or LDT
    uship8 ist;             // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
    uship8 type_attributes; // gate type, dpl, and p fields
    uship16 offset_2;        // offset bits 16..31
    uship32 offset_3;        // offset bits 32..63
    uship32 zero;            // reserved
};
void setup_idt();
#endif //UNTITLED_OS_IDT_H
