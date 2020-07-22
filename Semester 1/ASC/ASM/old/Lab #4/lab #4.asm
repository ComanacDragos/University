bits 32
global start 
extern exit 
import exit msvcrt.dll

segment data use32 class=data
    a db 10110011b
    b db 01110001b
    c db 0
    

segment code use32 class=code
    start:
    
    mov AL,[b]
    and AL,11100000b 
    shr AL, 5
    mov [c],AL ; c = 00000011
    
    and byte [c], 00000111b ; c = 00000011
    
    or byte [c], 01000000b ; c = 01000011
    
    mov AL,[b]
    not AL 
    and AL, 00001000b 
    shr AL,4
    or byte [c],AL
    
    
    
    
    
    mov DX,[c]
    
    push dword 0
    call [exit]