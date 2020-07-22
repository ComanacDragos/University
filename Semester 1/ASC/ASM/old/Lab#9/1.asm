bits 32
global start

extern exit, fread, fclose, fopen
import exit msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import fopen msvcrt.dll

segment data use32 class=data
    n db "ana.txt", 0
    m db "r", 0
    d_f dd -1
    buffer resb 100
    l equ $-buffer
    c dd 0

segment code use32 class=code
; citim toate caract dintr un fisier
    start:
    
    push m
    push n
    call [fopen]
    add ESP, 4*2
    
    cmp EAX, 0
    jz end
    
    mov [d_f], EAX
    
    .r 
        push dword [d_f]
        push l
        push 1
        push buffer
        call [fread]
        add ESP, 4*4
        
        add [c], EAX
        cmp EAX, l
        je .r
        
    push dword [d_f]
    call [fclose]
    add ESP, 4*1
    
    end:
    push dword 0
    call [exit]