bits 32
global start

extern exit, scanf, printf
import scanf msvcrt.dll
import printf msvcrt.dll
import exit msvcrt.dll

segment data

    msg1 db "Gib nr: ", 0
    msg2 db "Nr is: %d", 0
    f_d db "%d", 0

    a resd 1
    b resd 1
    k dd 5

segment code 

    start:
    push msg1
    call [printf]
    add ESP, 4*1
    
    push a
    push f_d
    call [scanf]
    add ESP, 4*2
    
    push msg1
    call [printf]
    add ESP, 4*1
    
    push b
    push f_d
    call [scanf]
    add ESP, 4*2
    
    mov EAX, [a]
    add EAX, [b]
    
    mul dword [k]
    
    push EAX
    push msg2
    call [printf]
    add ESP, 4*2
    
    
    
    
    push dword 0
    call [exit]