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
;the bits 16-21 of C have the value 101010 ; c[16-31] = [c+2] = 0000000000101010
;the bits 22-31 of C have the value 0
;the bits 32-42 of C are the same as the bits 21-31 of B
;the bits 43-55 of C are the same as the bits 1-13 of A  0001 1111 1111 1110
;the bits 56-63 of C are the same as the bits 24-31 of the result A XOR 0ABh
;    28-31  24-27  20-23  16-19   12-15  8-11   4-7    0-3                                  
; a = 0111   0111   0101   0111    1001  1011  1011   1110
;       7      7       5     7       9     B     B      E
; b = 1001   1011   1011   1110    0111  0111  0101   0111
;       9      B      B      E       7     7     5      7   

    start:
    mov EAX, [a]
    shr EAX, 21
    mov [c], AL ; c[0-7] = a[21-28]
    
    mov EAX, [b]
    not EAX
    shr EAX, 23
    mov [c+1], AL ; c[8-15] = b[23-30].complemented
    
    mov AX, 101010b
    mov [c+2], AX
    
    mov EAX, [b]
    shr EAX, 21
    mov [c+4], AX
    
    mov EAX, [a]
    mov EBX, 0011_1111_1111_1110b
    and EAX, EBX
    shl EAX, 10
    
    or [c+4], EAX ; bitii 11-23 din dword sup sunt ocupati
    
    mov EAX, [a]
    xor EAX, 0ABh
    shr EAX, 24
    mov [c+7], AL
    
    push dword 0
    call [exit]
    
    
    
    

    