//
// Created by oleg on 29.09.23.
//
#include "../include/memset.h"
#include "../include/stdint.h"

void *memset(void *ptr, ship value, size_ship num) {
    unsigned char *byte_ptr = (unsigned char *) ptr;
    unsigned char byte_value = (unsigned char) value;

    for (size_ship i = 0; i < num; i++) {
        *byte_ptr++ = byte_value;
    }

    return ptr;
}