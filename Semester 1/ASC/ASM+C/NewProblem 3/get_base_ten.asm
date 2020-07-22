bits 32
global _get_base_ten

segment data public data use32
    res_base resb 200
    
segment code public code use32
_get_base_ten:
    push EBP
    mov EBP, ESP
    pushad
    
    mov ESI, [EBP+8]
    mov ECX, [EBP+12]
    mov EDI, res_base
    
    loop1:
        lodsb
        cmp AL, '0'
        jb endLoop
        
        cmp AL, '9'
        ja endLoop
        
        stosb
        
    endLoop:
    loop loop1

    loop2:
        cmp dword [EDI], 0
        je endLoop2
        
        mov dword [EDI], 0
        inc EDI
        jmp loop2

    endLoop2:
       
    popad
    mov ESP,EBP
    pop EBP
    mov EAX, res_base
    ret

    
 
    