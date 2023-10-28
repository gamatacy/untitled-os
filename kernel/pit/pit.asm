global init_pit
section .text
align 4

init_pit:
    mov al, 00110100b 
    out 0x43, al    ;tell the PIT which channel we're setting
    mov ax, 61680
    out 0x40, al    ;send low byte
    mov al, ah
    out 0x40, al    ;send high byte
    ret