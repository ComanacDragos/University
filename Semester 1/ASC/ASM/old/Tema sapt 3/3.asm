bits 32
global start
extern exit
import exit msvcrt.dll

segment data use32 class=data

    a dw 2
    b dw 3
    c dw 4
    d dw 5

segment code use32 class=code
    start:
    mov AX,[a]
    add AX,[b]
    sub AX,[c]
    sub AX,[d]
    sub AX,[d]
push dword 0
call [exit]