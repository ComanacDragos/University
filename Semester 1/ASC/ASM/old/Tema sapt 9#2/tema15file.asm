bits 32
global start

extern exit, fprintf, fopen

import exit msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll

segment data use32 class=data:

    file db "file.txt", 0
    string db "A8Ha~aa*122+=aaaaaaaaa", 0
    len equ $-string
    newString times len+1 db 0
    X db 'X'
    m dd "w", 0
    fmt db "%s", 0
    d_file resd 1
    
segment code use32 class=code:
    start:
    
    
    mov ECX, len
    cmp ECX, 0
    jz end
    
    mov ESI, string
    mov EDI, newString
    loop1:
        lodsb 
        
        cmp AL, '0'
        jl checkUppercase
        
        cmp AL, '9'
        jg checkUppercase
        
        stosb 
        jmp endLoop
        
        checkUppercase:
        cmp AL, 'A'
        jl checkLowerCase
        
        cmp AL, 'Z'
        jg checkLowerCase
        
        stosb 
        jmp endLoop
        
        checkLowerCase:
        cmp AL, 'a'
        jl xLabel
        
        cmp AL, 'z'
        jg xLabel
    
        stosb 
        jmp endLoop
    
        xLabel:
           mov AL, [X]
           stosb
        
        endLoop:
    loop loop1
    
    push m
    push file
    call [fopen]
    add ESP, 4*2
    
    mov [d_file], EAX
    
    push newString
    push fmt
    push dword [d_file]
    call [fprintf]
    add ESP, 4*3
    
    
    
    
    end:
    push dword 0 
    call [exit]

    