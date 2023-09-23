#ifndef vga
#define vga
enum color {
    black=0,
    blue,
    green,
    cyan,
    red,
    purple,
    brown,
    gray,
    dark_gray,
    light_blue,
    light_green,
    light_cyan,
    light_red,
    light_purple,
    yellow,
    white
};

void set_fg(enum color fg);
void set_bg(enum color bg);
struct vga_char make_char(char value, enum color fg, enum color bg);
void putchar(char *c);
void reverse(char* str, int n);
void itoa(int num, char* str, int radix);
void print(const char *string);
void printf(const char* format, ...);
void clear();
#endif