#include <stdarg.h>
#include "vga.h"
struct vga_char;
struct char_with_color* const VGA_ADDRESS = (void*) 0xB8000;
static ship line = 0;
static ship pos = 0;
static enum vga_colors fg = VGA_COLOR_WHITE;
static enum vga_colors bg = VGA_COLOR_BLACK;

void set_fg(enum vga_colors _fg) {
    fg = _fg;
}

void set_bg(enum vga_colors _bg) {
    bg = _bg;
}

struct char_with_color make_char(char value, enum vga_colors fg, enum vga_colors bg) {
    struct char_with_color res = {
        .character = value,
        .color = fg + (bg << 4)
    };
    return res;
}

void scroll() {
    for (int i=1; i<VGA_HEIGHT; i++) {
        for (int j=0; j<VGA_WIDTH; j++) {
            VGA_ADDRESS[(i-1)*VGA_WIDTH+j] = VGA_ADDRESS[i*VGA_WIDTH+j];
        }
    }
    line = VGA_HEIGHT-1;
    pos = 0;
}

void putchar(char *c) {
    if (line >= VGA_HEIGHT) scroll();

    if (*c == '\n') {
        line++;
        pos = 0;
    } else {
        *(VGA_ADDRESS + line * VGA_WIDTH + pos) = make_char(*c, fg, bg);
        pos += 1;
        line += pos / 160;
        pos = pos % 160;
    }
}

void print(const char *string)
{
    while( *string != 0 )
    {
        putchar(string++);
    }
}

void reverse(char* str, ship n) {
    int i = 0;
    int j = n - 1;
    while (i < j) {
        char tmp = str[i];
        str[i++] = str[j];
        str[j--] = tmp;
    }
}

void itoa(ship num, char* str, ship radix) {
    ship i = 0;
    int is_negative = 0;
    if (num < 0) {
        is_negative = 1;
        num *= -1;
    }

    do {
        int rem = (num % radix);
        str[i++] = (rem > 9 ? 'a' - 10 : '0') + rem;
        num /= radix;
    } while (num);

    if (is_negative) str[i++] = '-';
    str[i] = 0;
    reverse(str, i);
}

void printf(const char* format, ...) {
    va_list varargs;
    va_start(varargs, format);
    char digits_buf[100];
    while (*format) {
        switch (*format) {
            case '%':
                format++;
                switch (*format) {
                    case 'd':
                        itoa(va_arg(varargs, int), digits_buf, 10);
                        print(digits_buf);
                        break;
                    case 'o':
                        itoa(va_arg(varargs, int), digits_buf, 8);
                        print(digits_buf);
                        break;
                    case 'x':
                        itoa(va_arg(varargs, int), digits_buf, 16);
                        print(digits_buf);
                        break;
                    case 'b':
                        itoa(va_arg(varargs, int), digits_buf, 2);
                        print(digits_buf);
                        break;
                    case 's':
                        print(va_arg(varargs, char*));
                        break;
                    case '%':
                        putchar("%");
                        break;
                    default:
                        putchar("#");
                }
                break;
            default:
                putchar(format);
        }
        format++;
    }
}

void clear() {
    for (ship i = 0; i < VGA_HEIGHT * VGA_WIDTH; i++) {
        (VGA_ADDRESS + i)->character=0;
        (VGA_ADDRESS + i)->color=0;
    }
    line = 0;
    pos = 0;
}