bits 32
global start

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a db "asdasihjihf"
    
segment code use32 class=data
    start:
    mov ESI, a
    mov EDI, a
    loopZERO:
        lodsb
        cmp AL, 0
        je endLoopZERO
        mov AL, 0
        stosb
        jmp loopZERO
    endLoopZERO:
    
    
    push dword 0
    call [exit]
    