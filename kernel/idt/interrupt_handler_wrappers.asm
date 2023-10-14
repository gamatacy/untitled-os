extern keyboard_handler
global keyboard_handler_wrapper
section .text
align 4
keyboard_handler_wrapper:
    push rax
    push rdi
    push rsi
    push rdx
    push rcx
    push r8
    push r9
    push r10
    push r11
    cld
    call keyboard_handler
    pop r11
    pop r10
    pop r9
    pop r8
    pop rcx
    pop rdx
    pop rsi
    pop rdi
    pop rax
    iret