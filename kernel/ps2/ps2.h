#ifndef PS2_H
#define PS2_H

#define PS2_DATA    0x60
#define PS2_COMMAND 0x64

/* Commands */
#define DISABLE_FIRST_PORT  0xAD
#define ENABLE_FIRST_PORT   0xAE
#define DISABLE_SECOND_PORT 0xA7
#define ENABLE_SECOND_PORT  0xA8
#define PS2_READ_BYTE       0x20
#define PS2_WRITE_BYTE      0x60

void ps2_init();

#endif // PS2_H