bits 32
global start

extern exit, fopen, fprintf
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll

segment data use32 class=data:
    
    fmt db "ana %s are %d mere", 0
    f db "ana.txt", 0
    m db "w", 0
    n db "Pop", 0
    d_f dd -1
   
   
   
segment code use32 class=code:
    start:
    
    push m
    push f
    call [fopen]
    
    cmp EAX, 0
    jz end
    
    mov [d_f], EAX
    add ESP, 4*2
    
    push 3
    push n
    push fmt
    push dword [d_f]
    
    call [fprintf]
    add ESP, 4*4
    
    end:
    
    push dword 0
    call [exit]