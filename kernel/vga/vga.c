
#include "vga.h"
#include "../lib/include/memset.h"
struct vga_char;
struct char_with_color *const VGA_ADDRESS = (void *) 0xB8000;
static ship line = 0;
static ship pos = 0;
static enum vga_colors fg = DEFAULT_FG_COLOR;
static enum vga_colors bg = DEFAULT_BG_COLOR;


void clear_vga() {
    memset(VGA_ADDRESS, 0, VGA_HEIGHT * VGA_WIDTH);
    line = 0;
    pos = 0;
}

void write_buffer(struct char_with_color *tty_buffer) {
    for (ship i = 0; i < VGA_HEIGHT * VGA_WIDTH; i++) {
        VGA_ADDRESS[i] = tty_buffer[i];
    }
}