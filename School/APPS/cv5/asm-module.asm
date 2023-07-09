bits 64

section .data  

section .text

global arrDiv
    arrDiv:
    mov rbx, 0
    mov ecx, edx
    mov r8d, 0
    fr:
        cmp ebx, esi
        jge ed

        mov edx, 0

        mov eax, [rdi + 4 * rbx]

        div ecx

        cmp edx, 0
        je increment

        sub [rdi + 4 * rbx], edx

        inc rbx
        jmp fr
    increment:
        inc r8d
        inc rbx
        jmp fr
    ed:
        mov eax, r8d
        mov r8d, 0
        ret

global fill_pyramid_numbers
    fill_pyramid_numbers:
        mov rbx, 0
        mov rcx, 1
        add rsi, 1
            for:
            cmp rcx, rsi
            jge end

            mov rax, rcx

            mul rcx

            add rax, rbx

            sub rcx, qword 1

            mov [rdi + 8 * rcx], rax

            mov rbx, rax

            add rcx, qword 1

            inc rcx
            jmp for

    end:
        ret

global change_array_by_avg
    change_array_by_avg:
        mov rax, 0
        mov rbx, 0
        mov rcx, 0
        f:
            cmp rax, rsi
            jge change

            add rbx, [rdi + 8 * rax]

            inc rax
            jmp f

    change:
        mov rax, rbx
        div rsi

        mov rbx, 0
        mov rcx, 0
            fo:
                cmp rbx, rsi
                jge end

                cmp [rdi + 8 * rbx], rax
                je chn
                jg cho
                jl chm

                inc rbx
                jmp fo

    chn:
        mov qword [rdi + 8 * rbx], 0
        inc rbx
        jmp fo

    cho:
        mov qword [rdi + 8 * rbx], 1
        inc rbx
        jmp fo

    chm:
        mov qword [rdi + 8 * rbx], -1
        inc rbx
        jmp fo
