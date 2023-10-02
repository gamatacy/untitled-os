#include "ps2.h"
#include "../lib/include/io.h"
#include "../lib/include/print.h"

// https://wiki.osdev.org/%228042%22_PS/2_Controller
void ps2_init() {
    // Disable devices
    outb(PS2_COMMAND, DISABLE_FIRST_PORT);
    outb(PS2_COMMAND, DISABLE_SECOND_PORT);
    
    // Flush the output buffer
    inb(PS2_DATA);

    // Set controller configuration byte
    outb(PS2_COMMAND, PS2_READ_BYTE);
    uint8_t config_byte = inb(PS2_DATA);

    uint8_t second_port_enabled = config_byte & (1<<5);
    printf("Second port enabled: %b\n", second_port_enabled);


}