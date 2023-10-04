#include <stdarg.h>
#include "vga.h"
#include "../tty/tty.h"

struct char_with_color* const VGA_ADDRESS = (void*) 0xB8000;
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

void scroll(uint8_t tty_id) {
    for (int i=1; i<VGA_HEIGHT; i++) {
        for (int j=0; j<VGA_WIDTH; j++) {
            terminals[tty_id].tty_buffer[(i-1)*VGA_WIDTH+j] = terminals[tty_id].tty_buffer[i*VGA_WIDTH+j];
        }
    }
    terminals[tty_id].line = VGA_HEIGHT-1;
    terminals[tty_id].pos = 0;
}

void putchar(uint8_t tty_id, char *c) {
    if (terminals[tty_id].line >= VGA_HEIGHT) scroll(tty_id);

    if (*c == '\n') {
        terminals[tty_id].line++;
        terminals[tty_id].pos = 0;
    } else {
        *(terminals[tty_id].tty_buffer + terminals[tty_id].line * VGA_WIDTH + terminals[tty_id].pos) = make_char(*c, fg, bg);
        terminals[tty_id].pos += 1;
        terminals[tty_id].line += terminals[tty_id].pos / VGA_WIDTH;
        terminals[tty_id].pos %= VGA_WIDTH;
    }
}

void print(uint8_t tty_id, const char *string)
{
    while( *string != 0 )
    {
        putchar(tty_id, string++);
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

void printf(uint8_t tty_id, const char* format, ...) {
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
                        print(tty_id, digits_buf);
                        break;
                    case 'o':
                        itoa(va_arg(varargs, int), digits_buf, 8);
                        print(tty_id, digits_buf);
                        break;
                    case 'x':
                        itoa(va_arg(varargs, int), digits_buf, 16);
                        print(tty_id, digits_buf);
                        break;
                    case 'b':
                        itoa(va_arg(varargs, int), digits_buf, 2);
                        print(tty_id, digits_buf);
                        break;
                    case 's':
                        print(tty_id, va_arg(varargs, char*));
                        break;
                    case '%':
                        putchar(tty_id, "%");
                        break;
                    default:
                        putchar(tty_id, "#");
                }
                break;
            default:
                putchar(tty_id, format);
        }
        format++;
    }
}

void clear(uint8_t tty_id) {
    for (ship i = 0; i < VGA_HEIGHT * VGA_WIDTH; i++) {
        (terminals[tty_id].tty_buffer + i)->character=0;
        (terminals[tty_id].tty_buffer + i)->color=0;
    }
    terminals[tty_id].line = 0;
    terminals[tty_id].pos = 0;
}

void flush(uint8_t tty_id) {
    for (ship i = 0; i < VGA_HEIGHT * VGA_WIDTH; i++) {
        VGA_ADDRESS[i] = terminals[tty_id].tty_buffer[i];
    }
}