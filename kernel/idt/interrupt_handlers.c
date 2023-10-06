//
// Created by oleg on 28.09.23.
//
#include "interrupt_handlers.h"
#include "../lib/include/io.h"
#include "../pic/pic.h"
#include "../vga/vga.h"
#include "../tty/tty.h"
#define F1 0x3B

struct interrupt_frame;

__attribute__((interrupt))  void divide_by_zero_handler(struct interrupt_frame* frame){
    clear_current_tty();
    print(current_tty, "division by zero\n");
    flush(current_tty);

    while(1) {
        asm ("hlt");
    }
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

        if (res >= F1 && res < F1 + TERMINALS) {
            switch_tty(res - F1);
        } else {
            printf(current_tty, "%x ", res);
        }
    }
    print(current_tty, "\n");
    outb(PIC1_COMMAND, PIC_EOI);
    // printf("Flags: %b\n", get_flags());
}