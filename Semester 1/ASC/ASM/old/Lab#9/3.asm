bits 32
global start

extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    f_str db "%s", 0
    buffer resb 100
    f_d db "%x", 0
    
segment code use32 class=code

    start:
    push buffer
    push f_str
    call [scanf]
    add ESP, 4*2
    
    mov EAX, 0
    mov AL, [buffer]
    
    push EAX
    push f_d
    call [printf]
    add ESP, 4*2
    
    
    push dword 0
    call [exit]