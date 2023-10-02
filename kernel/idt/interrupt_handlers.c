//
// Created by oleg on 28.09.23.
//
#include "interrupt_handlers.h"
#include "../lib/include/io.h"
#include "../pic/pic.h"
#include "../vga/vga.h"

struct interrupt_frame;

__attribute__((interrupt))  void divide_by_zero_handler(struct interrupt_frame* frame){
    clear();
    print("division by zero\n");
    while (1);
}


// static inline uint64_t get_flags() {
//     uint32_t flags;
//     asm volatile ( "pushf\npop %0" : "=r"(flags) : : "memory" );
//     return flags;
// }

__attribute__((interrupt)) void keyboard_handler(struct interrupt_frame* frame) {
    // printf("Flags: %b\n", get_flags());
    while (inb(0x64) & 1) {
        uint8_t res = inb(0x60);
        printf("%x ", res);
    }
    print("\n");
    outb(PIC1_COMMAND, PIC_EOI);
    // printf("Flags: %b\n", get_flags());
}