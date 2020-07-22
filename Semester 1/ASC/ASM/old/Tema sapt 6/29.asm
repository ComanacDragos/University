bits 32
global start
extern exit
import exit msvcrt.dll

segment data use32 class=data
        
    a dd 01110111010101111001101110111110b
    b dd 10011011101111100111011101010111b
    c dq 0

segment code use32 class=code   

;Given the doublewords A and B, obtain the quadword C as follows:
;the bits 0-7 of C are the same as the bits 21-28 of A
;the bits 8-15 of C are the same as the bits 23-30 of B complemented
;the bits 16-21 of C have the value 101010
;the bits 22-31 of C have the value 0
;the bits 32-42 of C are the same as the bits 21-31 of B
;the bits 43-55 of C are the same as the bits 1-13 of A
;the bits 56-63 of C are the same as the bits 24-31 of the result A XOR 0ABh
;    28-31  24-27  20-23  16-19   12-15  8-11   4-7    0-3                                  
; a = 0111   0111   0101   0111    1001  1011  1011   1110
;       7      7       5     7       9     B     B      E
; b = 1001   1011   1011   1110    0111  0111  0101   0111
;       9      B      B      E       7     7     5      7   
    start:
    mov EAX, [a]
    mov EBX, 00011111111000000000000000000000b
    and EAX,EBX ; EAX = a[21-28]
    
    mov CL,21
    shr EAX,CL 
    or dword [c],EAX ; c[0-7] = a[21-28]
    
    mov EAX, [b]
    not EAX
    add EAX,1 ; EAX = b.complemented
    
    mov EBX, 01111111100000000000000000000000b
    and EAX,EBX
    shr EAX,15 ; EAX[8-15] = b.complemented[23-30]
    or dword [c], EAX ; c[8-15] = b.complemented[23-30]
    
    mov EAX, 00000000001010100000000000000000b
    or dword [c], EAX ; c[16-21] = 101010
    
    ;bits 22-31 are already 0 because the starting value of c was 0
    
    mov EAX, [b]
    mov EBX, 11111111111000000000000000000000b
    and EAX,EBX
    shr EAX,21
    or dword [c+4], EAX ; c[32-42] = b[21-31]
    
    mov EAX, [a]
    mov EBX, 00000000000000000011111111111110b
    and EAX,EBX
    shl EAX,10
    or dword [c+4], EAX ; c[43-55] = a[1-13]
   
    mov EAX, [a]
    xor EAX, 0ABh 
    shr EAX, 24
    mov [c+7],AL ; c[56-63] = A xor 0ABh [24-31]
    
     
    
    
    mov ECX, dword [c]
    mov EDX, dword [c+4] ; EDX:ECX = c
    
    push dword 0
    call [exit]