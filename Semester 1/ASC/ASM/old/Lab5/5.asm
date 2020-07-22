bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    s dd 12345678h, 1A2C3C4Dh, 98FCDD76h, 12783B2Bh
    len equ ($-s)/4
    d resd 1


segment code use32 class=code
    start:
    mov ESI, s
    mov EDI, d
    mov ECX, len
    mov EDX, 0 ; contor pt nr de octeti inserati in d
    
    loop1:
        lodsd
        ;shr AX, 8
        ;mov AH, 0
        ;mov BL, AL
        
        ;mov BH, 2
        ;div BH ; AL = AX/2 ; AH = AX%2
        
        ;cmp AH, 0
        
        test AH, 01h ; --> 01 daca nr este impar ; 00 daca este par ; test <=> and fictiv
        jnz endLoop1
        
        mov AL, AH
        stosb
        inc EDX
        
    endLoop1:
    loop loop1
    
    loop2:
        cmp EDX, 4
        je endLoop2
        
        mov AL, 0FFh
        stosb
        inc EDX
        
    jmp loop2
    endLoop2:
    
    
    push dword 0
    call [exit]