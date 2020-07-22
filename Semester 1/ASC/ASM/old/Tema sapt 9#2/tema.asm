bits 32
global start

extern exit, fopen ,fprintf, scanf, printf

import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data:

    m1 db "Give name: ", 0
    m2 db "Give number: ", 0

    fmt db "ana %s are %d mere", 0
    file db "file.txt", 0
    m db "w", 0
    n resb 10
    d_f dd -1
    mere resd 1
    f_str db "%s", 0
    f_d db "%d", 0
  
segment code use32 class=code:
    start:
    
    push m
    push file
    call [fopen]
    add ESP, 4*2
    
    cmp EAX, 0
    jz end
    mov [d_f], EAX
    
    push m1
    call [printf]
    add ESP, 4*1
    
    push n
    push f_str
    call [scanf]
    add ESP, 4*2
    
    push m2
    call [printf]
    add ESP, 4*1
    
    push mere
    push f_d
    call [scanf]
    add ESP, 4*2
    
    push dword [mere]
    push n
    push fmt
    push dword [d_f]
    call [fprintf]
    add ESP, 4*4
    
    
    end:
    push dword 0
    call [exit]