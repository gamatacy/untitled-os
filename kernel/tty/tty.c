#include <stdarg.h>
#include "tty.h"
#include "../lib/include/stdint.h"
#include "../lib/include/memset.h"
#define TERMINALS_NUMBER 7
static struct tty_structure tty_terminals[TERMINALS_NUMBER];
static struct tty_structure* active_tty;

void set_fg(enum vga_colors _fg) {
    active_tty->fg = _fg;
}

void set_bg(enum vga_colors _bg) {
    active_tty->bg = _bg;
}

void init_tty(){
    memset(&tty_terminals, 0, sizeof(struct tty_structure) * TERMINALS_NUMBER);
    for (ship i = 0; i < TERMINALS_NUMBER; ++i) {
        (tty_terminals+i)->tty_id = i;
        (tty_terminals+i)->bg = DEFAULT_BG_COLOR;
        (tty_terminals+i)->fg = DEFAULT_FG_COLOR;
        (tty_terminals+i)->line = (tty_terminals+i)->pos = 0;
        memset((tty_terminals+i)->tty_buffer, 0, VGA_HEIGHT * VGA_WIDTH);
    }
    set_tty(0);
};

void set_tty(uship8 terminal){
    if(TERMINALS_NUMBER<=terminal){
        return;
    }
    clear_vga();
    active_tty = tty_terminals+terminal;
    write_buffer(active_tty->tty_buffer);
}

void clear_current_tty(){
    memset(active_tty->tty_buffer, 0, VGA_WIDTH*VGA_HEIGHT);
    active_tty->pos = 0;
    active_tty->line = 0;
    clear_vga();
}
uship8 get_current_tty(){
    return active_tty->tty_id;
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

struct char_with_color make_char(char value, enum vga_colors fg, enum vga_colors bg) {
    struct char_with_color res = {
            .character = value,
            .color = fg + (bg << 4)
    };
    return res;
}

void putchar(char *c) {
//    if (active_tty->line >= VGA_HEIGHT) scroll(tty_id);

    if (*c == '\n') {
        active_tty->line++;
        active_tty->pos = 0;
    } else {
        *(active_tty->tty_buffer + active_tty->line * VGA_WIDTH + active_tty->pos) = make_char(*c, active_tty->fg, active_tty->bg);
        active_tty->pos += 1;
        active_tty->line += active_tty->pos / VGA_WIDTH;
        active_tty->pos %= VGA_WIDTH;
    }
}

void print(const char *string) {
    while (*string != 0) {
        putchar(string++);
    }
    write_buffer(active_tty->tty_buffer);
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
                        write_buffer(active_tty->tty_buffer);
                }
                break;
            default:
                putchar(format);
                write_buffer(active_tty->tty_buffer);
        }
        format++;
    }
}