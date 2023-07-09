
    bits 64
    section .data

    extern help

;***************************************************************************

    section .text

global cislice
    cislice:
        mov rbx, 0
        mov rcx, 0
        mov rdx, 0
        loop:
            cmp byte [rax + 1 * rbx], 0
            je end


            cmp byte [rax + 1 * rbx], '0'
            je up
            cmp byte [rax + 1 * rbx], '1'
            je up
            cmp byte [rax + 1 * rbx], '2'
            je up
            cmp byte [rax + 1 * rbx], '3'
            je up
            cmp byte [rax + 1 * rbx], '4'
            je up
            cmp byte [rax + 1 * rbx], '5'
            je up
            cmp byte [rax + 1 * rbx], '6'
            je up
            cmp byte [rax + 1 * rbx], '7'
            je up
            cmp byte [rax + 1 * rbx], '8'
            je up
            cmp byte [rax + 1 * rbx], '9'
            je up

            cmp rcx, rdx
            jg change

            mov rcx, 0
            inc rbx
            jmp loop

            change:
                mov rdx, rcx
                mov rcx, 0
                inc rbx
                jmp loop

            up:
                inc rcx
                inc rbx
                jmp loop

            end:
                mov rax, rdx
                ret

global nahradit:
    nahradit:
        mov ebx, 0
        mov ecx, 0
        mov edx, 0
        l:
            cmp byte [eax + 1 * ebx], 0
            je end

            cmp byte [eax + 1 * ebx], '('
            je nsmile

            cmp byte [eax + 1 * ebx], ')'
            je smile

            inc ebx
            jmp l

            smile:
                mov byte [eax + 1 * ebx], ':'

                inc ebx
                jmp l

            nsmile:
                mov byte [eax + 1 * ebx], ':'

                inc ebx
                jmp l

global prvni_bit
    prvni_bit:
        mov edi, eax
        mov eax, 2
        mov ebx, 2
        mov edx, 0
        smycka:
            mov ecx, edi
            and	ecx, 1
            jz end



            inc edx
            jmp smycka

