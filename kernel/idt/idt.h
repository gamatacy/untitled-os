//
// Created by oleg on 28.09.23.
//

#ifndef UNTITLED_OS_IDT_H
#define UNTITLED_OS_IDT_H
#include "./stdint.h"
#define NUM_IDT_ENTRIES 256

struct IDTR {
    uint16_t limit;           // IDT size
    uint64_t base;            // IDT pointer
} __attribute__((packed));

struct InterruptDescriptor64 {
    uint16_t offset_1;        // offset bits 0..15
    uint16_t selector;        // a code segment selector in GDT or LDT
    uint8_t ist;             // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
    uint8_t type_attributes; // gate type, dpl, and p fields
    uint16_t offset_2;        // offset bits 16..31
    uint32_t offset_3;        // offset bits 32..63
    uint32_t zero;            // reserved
};
void setup_idt();
#endif //UNTITLED_OS_IDT_H
