bits 32
global start

extern exit
import exit msvcrt.dll



segment data

    s1 db ".dra abc ddd." 
    len1 equ $-s1
    s2 db "dra"
    len2 equ $-s2
    
    ;aux resb len2
    dest resb len1
    
    
segment code

    start:
    mov ECX, len1
    mov ESI, s1
    mov EDI, dest
    
    loop1:
        push ECX
        push ESI
        
        mov ECX, len2
        mov EBX, s2
        mov EDX, 0
        loop2:
            lodsb ; AL = s1[i]
            inc EDX
            cmp AL, [EBX]
            jne notEqual
            inc EBX
            
        loop loop2
        add ESP, 4
        pop ECX
        sub ECX, len2-1
        jmp endLoop1
        
        
        ; repz cmpsb
        
        notEqual:
        pop ESI
        lodsb
        stosb
        inc ESI
        pop ECX
        
    endLoop1:
    
    loop loop1
        
        
    push dword 0
    call [exit]