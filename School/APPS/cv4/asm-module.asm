
    bits 64
    section .data

    extern help

;***************************************************************************

    section .text

global my_strcpy
    my_strcpy:
        mov rcx, 0
        fr:
            cmp rcx, rdx
            jge end

            mov al, [rsi + rcx * 1]
            mov [help], al
            mov [rdi + rcx * 1], al

            inc rcx
            jmp fr

    end:
        mov [help], byte 0
        ret

global my_strchr
    my_strchr:
        mov rcx, 0
        mov rax, 0
        mov [help], sil
        add [help], dword 32
        for:
            cmp byte [rdi + 1 * rcx], 0
            je end

            mov al, [rdi + rcx * 1]
            cmp sil, al
            je plus
            cmp [help], al
            je plus

            inc rcx
            jmp for

    plus:
        cmp rax, 0
        jl moveIt
        inc rcx
        inc rdx
        jmp for

    moveIt:
        mov rax, rcx


