    

    bits 64

    section .data

    extern longs;
    extern max;

;***************************************************************************

    section .text

    global change
        mov ebx, 0
        mov eax, 0
        change:
            cmp ebx, 10
            jge done
            mov rax, [longs + ebx * 4]
            and	rax, 1
            jz even
        even:
            neg rax
            mov [longs + ebx * 4], rax
            inc ebx
            jmp change
        done:
            ret


        
                

            


            
    

