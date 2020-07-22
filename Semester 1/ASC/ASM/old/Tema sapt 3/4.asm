bits 32
global start
extern exit
import exit msvcrt.dll

segment data use32 class=data

    a db 2
    b db 4
    c db 4
    d dw 5
    
segment code use32 class=code
    start:
    ; a*2+2*(b-3)-d-2*c
    mov AL,2 ; AL=a=2
    mul byte [a] ; AX=a*2=4
    mov BX,AX ; BX=4
    mov AL,[b] ; AL=4
    sub AL,3 ; AL=1=
    mov CL,2 ; CL=2
    mul CL ; AL=2
    add BX,AX ; BX=6
    sub BX,[d] ; BX=1
    mov AL,[c] ; AL=4
    mov CL,2 ; CL=2
    mul CL ; AL=8
    sub BX,AX ; BX=1-8=-7
push dword 0
call [exit]