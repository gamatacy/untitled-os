global init_pit
global send_values_to_sched
global stop_timer
section .text
align 4

init_pit:
    ; bits:
    ; 0 - binary/binary decimal
    ; 1:3 - Channel operating mode
    ; 4:5 - Read/Write Mode
    ; 6-7 - Channel selection
    mov al, 00111000b
    ; Port 43 for setting the timer
    out 0x43, al    ;tell the PIT which channel we're setting

send_values_to_sched:
    mov ax, 61680
    out 0x40, al    ;send low byte
    mov al, ah
    out 0x40, al    ;send high byte
    ret

stop_timer:
    mov ax, 0
    out 0x40, al    ;send low byte
    mov al, ah
    out 0x40, al    ;send high byte
    ret