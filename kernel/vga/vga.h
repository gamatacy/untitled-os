#ifndef UNTITLED_OS_PRINT_H
#define UNTITLED_OS_PRINT_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_COLOR 7
#include "../lib/include/stdint.h"
enum vga_colors{
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GRAY = 7,
    VGA_COLOR_DARK_GRAY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_YELLOW = 14,
    VGA_COLOR_WHITE = 15
};
struct __attribute__((packed)) char_with_color {
    uship8 character;
    uship8 color;
};

void set_fg(enum vga_colors fg);
void set_bg(enum vga_colors bg);
void itoa(int num, char* str, int radix);
void print(const char *string);
void printf(const char* format, ...);
void clear();
#endif //UNTITLED_OS_PRINT_H