global start

section .text
bits 32
start:
    ; point first entry of p4 table to the first entry in p3 table
    mov eax, p3_table
    ; make first two bits 1
    ; present bit - page is currently in memory
    ; writable bit - page allowed to be written to
    or eax, 0b11
    mov dword [p4_table + 0], eax

    mov eax, p2_table
    or eax, 0b11
    mov dword [p3_table + 0], eax
    
    mov ecx, 0 ; counter
.map_p2_table:
    mov eax, 0x200000 ; 2MiB
    mul ecx
    or eax, 0b10000011
    mov [p2_table + ecx * 8], eax

    inc ecx
    cmp ecx, 512
    jne .map_p2_table
    hlt

section .bss
align 4096

p4_table:
    resb 4096
p3_table:
    resb 4096
p2_table:
    resb 4096