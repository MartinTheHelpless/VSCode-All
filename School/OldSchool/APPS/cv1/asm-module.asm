    

    bits 64

    section .data

    extern  data
    extern dta

    extern extended
    extern key

    extern dat
    extern result
;***************************************************************************

    section .text

    global swap_endiannes

    swap_endiannes:

        mov ah,[data + 0]
        mov bh,[data + 1]
        mov ch,[data + 2]
        mov dh,[data + 3]
        mov  [data + 3], ah
        mov  [data + 2], bh
        mov  [data + 1], ch
        mov  [data + 0], dh
        ret

    global replace

    replace:

        mov dword [dta + 0], "B"
        mov dword [dta + 1], "U"
        mov dword [dta + 2], "R"
        mov dword [dta + 3], "0"
        mov dword [dta + 4], "2"
        mov dword [dta + 5], "6"
        mov dword [dta + 6], "6"
        ret


    global extend

    extend:
        
        movsx rax, word [key]
        mov [extended], rax


    global compose

    compose:
        
        mov eax, dword [dat]
        mov [result], eax
        ret


    


