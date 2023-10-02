//
// Created by oleg on 28.09.23.
//

#include "idt.h"
#include "interrupt_handlers.h"
#include "../lib/include/memset.h"
#include "../lib/include/io.h"
#include "../lib/include/print.h"
#include "../pic/pic.h"

void setup_idt(){
    struct InterruptDescriptor64 idt[NUM_IDT_ENTRIES]; // Создаем массив для 256 дескрипторов (для всех возможных прерываний)
    // Настройка регистра IDTR
    struct IDTR idtr;
    idtr.limit = sizeof(struct InterruptDescriptor64) * NUM_IDT_ENTRIES - 1;
    idtr.base = (uint64_t)&idt;
    memset(&idt, 0, sizeof(struct InterruptDescriptor64) * NUM_IDT_ENTRIES);
    // Настроим дескриптор IDT для деления на ноль (INT 0x0)
    idt[0].offset_1 = (uint16_t)((uintptr_t)divide_by_zero_handler);
    idt[0].selector = 0x08; // Селектор сегмента кода (обычно 0x08)
    idt[0].type_attributes = 0x8E; // Тип и атрибуты дескриптора (прерывание с пользовательским уровнем доступа)
    idt[0].offset_2 = (uint16_t)(((uintptr_t)divide_by_zero_handler) >> 16);
    idt[0].offset_3 = (uint32_t)(((uintptr_t)divide_by_zero_handler) >> 32);

    idt[PIC_MASTER_OFFSET + 1].offset_1 = (uint16_t)((uintptr_t)keyboard_handler);
    idt[PIC_MASTER_OFFSET + 1].selector = 0x08; // Селектор сегмента кода (обычно 0x08)
    idt[PIC_MASTER_OFFSET + 1].type_attributes = 0x8E; // Тип и атрибуты дескриптора (прерывание с пользовательским уровнем доступа)
    idt[PIC_MASTER_OFFSET + 1].offset_2 = (uint16_t)(((uintptr_t)keyboard_handler) >> 16);
    idt[PIC_MASTER_OFFSET + 1].offset_3 = (uint32_t)(((uintptr_t)keyboard_handler) >> 32);


    // Загрузка IDTR
    asm volatile ("lidt %0" : : "m"(idtr));

    pic_init();

    outb(PIC1_DATA,0xff);
    outb(PIC2_DATA,0xff);

    outb(PIC1_DATA, ~(1<<1));

    asm("sti");
}
