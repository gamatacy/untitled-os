#ifndef UNTITLED_OS_PRINT_H
#define UNTITLED_OS_PRINT_H
#include "vga.h"
void set_fg(enum vga_colors fg);
void set_bg(enum vga_colors bg);
struct vga_char make_char(char value, enum vga_colors fg, enum vga_colors bg);
void putchar(char *c);
void reverse(char* str, int n);
void itoa(int num, char* str, int radix);
void print(const char *string);
void printf(const char* format, ...);
void clear();
#endif //UNTITLED_OS_PRINT_H