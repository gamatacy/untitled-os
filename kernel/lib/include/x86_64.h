//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//

#ifndef X86_64_H
#define X86_64_H
#include "stdint.h"

static inline void
cli(void) {
    asm volatile("cli");
}

static inline void
sti(void)
{
    asm volatile("sti");
}


static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) :"memory");
}

static inline void outw(uint16_t port, uint16_t val) {
    asm volatile ( "outw %0, %1" : : "a"(val), "Nd"(port) :"memory");
}

static inline void outl(uint16_t port, uint32_t val) {
    asm volatile ( "outl %0, %1" : : "a"(val), "Nd"(port) :"memory");
}

static inline uint8_t inb(uint16_t port) {
    uint8_t res;
    asm volatile ( "inb %1, %0" : "=a"(res) : "Nd"(port) : "memory");
    return res;
}

static inline uint16_t inw(uint16_t port) {
    uint16_t res;
    asm volatile ( "inw %1, %0" : "=a"(res) : "Nd"(port) : "memory");
    return res;
}

static inline uint32_t inl(uint16_t port) {
    uint32_t res;
    asm volatile ( "inl %1, %0" : "=a"(res) : "Nd"(port) : "memory");
    return res;
}

static inline uint xchg(volatile uint *addr, uint newval) {
    uint result;

    // The + in "+m" denotes a read-modify-write operand.
    asm volatile("lock; xchgl %0, %1" :
            "+m" (*addr), "=a" (result) :
            "1" (newval) :
            "cc");
    return result;
}


static inline uint32_t
readeflags(void)
{
    uint64_t eflags;
    asm volatile("pushf; pop %0" : "=r" (eflags));
    return eflags;
}

#endif // X86_64_H