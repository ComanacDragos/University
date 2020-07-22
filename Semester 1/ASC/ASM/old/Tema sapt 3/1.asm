bits 32
global start
extern exit
import exit msvcrt.dll

segment data use32 class=data
   

segment code use 32 class=code
    start:
    ; 6*3
    mov AL,6
    mov BL,3
    mul BL
    push dword 0
    call [exit]