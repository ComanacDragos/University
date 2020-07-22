bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data


segment code use32 class=code
; 
    start:
    mov AX, -23
    mov bl, 10
    idiv bl
    push dword 0
    call [exit]