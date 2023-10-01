//
// Created by oleg on 28.09.23.
//

#include "idt.h"
#include "interrupt_handlers.h"
#include "../lib/include/memset.h"
#define MAX_INTERRUPTS 256
void make_interrupt(struct InterruptDescriptor64* idt, int array_index, uintptr_t handler){
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
    // Настроим дескриптор IDT для деления на ноль (INT 0x0)
    make_interrupt(idt, 0, (uintptr_t)divide_by_zero_handler);
    // Загрузка IDTR
    asm volatile ("lidt %0" : : "m"(idtr));
}
