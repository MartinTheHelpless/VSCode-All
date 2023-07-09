
    bits 64
    section .data

    extern data;
    extern res;
    extern length;

    extern fib;
    extern resF;

    extern pal;
    extern pt;

;***************************************************************************

    section .text

global min

    min:
        mov eax, 0
        mov ebx, [data + eax * 4] 
        for:
            cmp eax, [length]
            jge nxt

            cmp [data + eax * 4], ebx
            jl mn

            inc eax
            jmp for
    mn:
        mov ebx, [data + eax * 4]
        inc eax
        jmp for
    nxt:
        mov eax, 0
            rof:
                cmp eax, [length]
                jge end

                cmp ebx, 0
                jge end
                jg subt
                jl ad

                inc eax
                jmp rof

        subt:
            sub [data + eax * 4], ebx
            inc eax
            jmp rof
        
        ad:
            add [data + eax * 4], ebx
            inc eax
            jmp rof




global fibonacci
    fibonacci:
        mov ebx, 1
        mov eax, 1
        mov ecx, 1
        mov edx, 1
        fr:
            cmp ebx, [fib]
            jge end

            add eax, ecx
            mov [resF], eax
            mov ecx, edx
            mov edx, eax
            
            inc ebx
            jmp fr

        end:
            ret

global palindrom
    palindrom:
        mov eax, 0
        mov ebx, 5
            f:
                cmp eax, ebx
                jge end

                mov cl, [pal + eax * 1]
                cmp cl, [pal + ebx * 1]
                jne nPal

                inc eax
                dec ebx
                jmp f

        nPal:
            mov [pt], dword 1
            ret

