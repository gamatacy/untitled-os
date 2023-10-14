#include "stdint.h"

#ifndef IO_H
#define IO_H

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

#endif // IO_H