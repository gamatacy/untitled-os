section .text
    global switch_context

; Контекстное переключение
;
;   void switch_context(struct context **old, struct context *new);
;
; Сохраняет текущие значения регистров в стеке, создавая
; структуру context, и сохраняет её адрес в *old.
; Переключает стек на новый и извлекает ранее сохранённые значения регистров.

switch_context:
    ; Загружаем адрес структуры context из стека в eax
    mov eax, [rsp + 8]

    ; Загружаем адрес нового контекста из стека в rdx
    mov rdx, [rsp + 16]

    ; Сохраняем значения callee-saved регистров
    push r15
    push r14
    push r13
    push r12
    push r11
    push r10
    push r9
    push r8
    push rbp
    push rdi
    push rsi
    push rdx
    push rcx
    push rbx
    push rax

    ; Переключаем стеки
    mov [rax], rsp
    mov rsp, rdx

    ; Восстанавливаем значения callee-saved регистров нового контекста
    pop rax
    pop rbx
    pop rcx
    pop rdx
    pop rsi
    pop rdi
    pop rbp
    pop r8
    pop r9
    pop r10
    pop r11
    pop r12
    pop r13
    pop r14
    pop r15
    ; Возвращаемся из функции
    ret
