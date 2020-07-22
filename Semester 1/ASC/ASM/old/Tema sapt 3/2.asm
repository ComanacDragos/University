bits 32
global start
extern exit
import exit msvcrt.dll

segment data use32 class=data  
    a db 1
    b db 2
    c db 3
    d db 4
    
segment code use 32 class=code
    start:
    mov AX,[a] ; AX=1
    sub AX,[b] ; AX=1-2=-1
    sub AX,[d] ; ;AX=-1-4=-5
    add AX,2 ; AX=-3
    add AX,[c] ; AX=0
    mov BX,10 ; BX=10
    sub BX,[b] ; BX=8
    add AX,BX ; AX=8
    push dword 0
    call [exit]