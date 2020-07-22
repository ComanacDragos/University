bits 32
global start
extern exit, gets, printf, fread, fopen, fclose
import exit msvcrt.dll
import gets msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll

segment data
    format db "%c", 0
    file db "fisier.txt", 0
    mode db "r", 0
    descriptor dd 0
    s resb 100
    

segment code
    start:
    push mode
    push file
    call [fopen]
    add esp, 4*2
    
    mov [descriptor], EAX
    
    push dword [descriptor]
    push 100
    push 1
    push s
    call [fread]
    add esp, 4*4
    
    
    mov esi, s
    loop1:
        lodsb
        cmp al, 0
        je endLoop1
        
        cmp al, 'A'
        jl endLoop
        
        cmp AL, 'Z'
        jg notUpper
        
        sub AL, 2
        cmp AL, 'A'
        jge endLoop
        
        add AL, 'z'-'a'+1
        
        jmp endLoop
        
        
        
        notUpper:
        cmp AL, 'a'
        jl endLoop
        
        cmp AL, 'z'
        jg endLoop
        
        ;letter: lower:
        sub AL, 2
        
        cmp AL, 'a'
        jge endLoop
        
        add AL, 'z'-'a'+1
        ;add AL, 2
        
        
    endLoop:
    
    mov EBX, 0
    mov BL, AL
    push EBX
    push format
    call [printf]
    add esp, 4*2
    jmp loop1
    endLoop1:
    
    
    push dword [descriptor]
    call [fclose]
    add esp ,4
    
    push dword 0
    call [exit]
    