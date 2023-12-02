//
// Created by oleg on 28.09.23.
//

#include "idt.h"
#include "interrupt_handlers.h"
#include "../lib/include/memset.h"
#include "../pic/pic.h"
#include "../pit/pit.h"

#define MAX_INTERRUPTS 256
void make_interrupt(struct InterruptDescriptor64* idt, ship array_index, uintptr_t handler){
    if(array_index>=MAX_INTERRUPTS)return;
    idt[array_index].offset_1 = (uint16_t)handler;
    idt[array_index].selector = 0x08; // Селектор сегмента кода (обычно 0x08)
    idt[array_index].type_attributes = 0x8E; // Тип и атрибуты дескриптора (прерывание с пользовательским уровнем доступа)
    idt[array_index].offset_2 = (uint16_t)((handler) >> 16);
    idt[array_index].offset_3 = (uint32_t)((handler) >> 32);
}

void setup_idt(){
    struct InterruptDescriptor64 idt[MAX_INTERRUPTS]; // Создаем массив для 256 дескрипторов (для всех возможных прерываний)
    // Настройка регистра IDTR
    struct IDTR idtr;
    idtr.limit = sizeof(struct InterruptDescriptor64) * MAX_INTERRUPTS - 1;
    idtr.base = (uint64_t)&idt;
    memset(&idt, 0, sizeof(struct InterruptDescriptor64) * MAX_INTERRUPTS);
    for (int i = 0; i < MAX_INTERRUPTS; ++i) {
        make_interrupt(idt, i, (uintptr_t)default_handler);
    }
    // Настроим дескриптор IDT для деления на ноль (INT 0x0)
    make_interrupt(idt, 0, (uintptr_t)divide_by_zero_handler);
    make_interrupt(idt, PIC_MASTER_OFFSET, (uintptr_t)timer_interrupt);
    make_interrupt(idt, PIC_MASTER_OFFSET+1, (uintptr_t)keyboard_handler);
    make_interrupt(idt, 14, (uintptr_t)penis_interrupt);

    // Загрузка IDTR
    asm volatile ("lidt %0" : : "m"(idtr));

    pic_init();
    init_pit();

    outb(PIC1_DATA,0xff);
    outb(PIC2_DATA,0xff);

    outb(PIC1_DATA, ~(1<<0 | 1<<1));

    asm("sti");
}
