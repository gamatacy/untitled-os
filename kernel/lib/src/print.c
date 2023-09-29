#include "../include/stdint.h"
#include <stdarg.h>
#include "../include/print.h"

static struct vga_char *video = (void*)0xB8000;
static const int LINE_COUNT = 25;
static const int POS_COUNT  = 80;
static int line = 0;
static int pos = 0;
static enum color fg = white;
static enum color bg = black;

struct __attribute__((packed)) vga_char {
    uint8_t character;
    uint8_t color;
};

void set_fg(enum color _fg) {
    fg = _fg;
}

void set_bg(enum color _bg) {
    bg = _bg;
}

struct vga_char make_char(char value, enum color fg, enum color bg) {
    struct vga_char res = {
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
        *(video + line * POS_COUNT + pos) = make_char(*c, fg, bg);
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

void reverse(char* str, int n) {
    int i = 0;
    int j = n - 1;
    
    while (i < j) {
        char tmp = str[i];
        str[i++] = str[j];
        str[j--] = tmp;
    }
}

void itoa(int num, char* str, int radix) {
    int i = 0;

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
    for (int i = 0; i < LINE_COUNT * POS_COUNT; i++) {
        (video + i)->character=0;
        (video + i)->color=0;
    }
    line = 0;
    pos = 0;
}