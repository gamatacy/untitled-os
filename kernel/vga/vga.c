
#include <stdarg.h>
#include "vga.h"
#include "../lib/include/memset.h"
struct vga_char;
struct char_with_color *const VGA_ADDRESS = (void *) 0xB8000;
static ship line = 0;
static ship pos = 0;
static enum vga_colors fg = DEFAULT_FG_COLOR;
static enum vga_colors bg = DEFAULT_BG_COLOR;

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

void putchar(char *c) {
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

void print(const char *string) {
    while (*string != 0) {
        putchar(string++);
    }
}


void reverse(char *str, ship n) {
    int i = 0;
    int j = n - 1;
    while (i < j) {
        char tmp = str[i];
        str[i++] = str[j];
        str[j--] = tmp;
    }
}

void itoa(ship num, char *str, ship radix) {
    ship i = 0;
    int is_negative = 0;
    if (num < 0) {
        is_negative = 1;
        num *= -1;
    }
    while (num) {
        int rem = (num % radix);
        str[i++] = (rem > 9 ? 'a' : '0') + rem;
        num /= radix;
    }
    if (is_negative) str[i++] = '-';
    str[i] = 0;
    reverse(str, i);
}

void printf(const char *format, ...) {
    va_list varargs;
    va_start(varargs, format);
    char digits_buf[100];
    while (*format) {
        switch (*format) {
            case '%':
                format++;
                switch (*format) {
                    case 'd':
                        itoa(va_arg(varargs,
                        int), digits_buf, 10);
                        print(digits_buf);
                        break;
                    case 'o':
                        itoa(va_arg(varargs,
                        int), digits_buf, 8);
                        print(digits_buf);
                        break;
                    case 'x':
                        itoa(va_arg(varargs,
                        int), digits_buf, 16);
                        print(digits_buf);
                        break;
                    case 's':
                        print(va_arg(varargs,
                        char*));
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

void clear_vga() {
    memset(VGA_ADDRESS, 0, VGA_HEIGHT * VGA_WIDTH);
    line = 0;
    pos = 0;
}

int write_buffer(struct char_with_color *tty_buffer, int size) {
    if(size>VGA_HEIGHT * VGA_WIDTH){
        return 1;
    }
    for (ship i = 0; i < size; i++) {
        VGA_ADDRESS[i] = tty_buffer[i];
    }
    return 0;
}