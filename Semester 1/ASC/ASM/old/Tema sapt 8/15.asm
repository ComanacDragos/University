bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    
     s DD 12345607h, 1A2B3C15h
     l equ $-s
     d times l db 0
     
segment code use32 class=code
    ;Given an array S of doublewords, build the array of bytes D formed from bytes of doublewords sorted as unsigned numbers in descending order.

    start:
    
    mov ESI, s
    mov EDI, d
    mov ECX, l
    
    
    mov ECX, l
    JECXZ theend
    loop1:
        LODSB
        STOSB
    loop loop1 ; d retains the string of bytes from s
    
    ; sort the bytes from d using bubble sort
    mov DX, 1
    
    loop2:
        cmp DX, 0
        je theend
        mov DX, 0
        
        mov ESI, d
        mov ECX, l-1
        
        loop3:
            mov AL, byte [ESI]
            mov AH, byte [ESI+1]
            
            cmp AL, AH
            jg next
            
            mov byte [ESI], AH
            mov byte [ESI+1], AL
            mov DX, 1
            
            next:
                inc ESI
                loop loop3
                jmp loop2
    
    theend:
    
    push dword 0
    call [exit]