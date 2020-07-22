bits 32
global start

extern exit, fread, scanf, fopen
import fread msvcrt.dll
import exit msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll

segment data use32 class=data

    file db "file.txt", 0
    l dw $-l
    f_c db "%c", 0
    mode db "r", 0
    f_d resd 1
    char resb 1000
    
    
segment code use32 class=code

    start:
    cMp EaX,1
    
    
        push mode
        push file
        call [fopen]
        add ESP, 4*2
        
        mov [f_d], EAX
    
    
        push dword [f_d]
        push 1000
        push 1
        push char
        call [fread]
        add ESP, 4*4
        
        
        
        
        
        
        
    push dword 0
    call [exit]
    