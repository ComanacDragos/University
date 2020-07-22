bits 32
global _base10
;global _concatenate

segment data public data use32
    
    res_base resb 100
    res_conc resb 200
    
segment code public code use32
_base10:
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

    
    popad
    mov ESP,EBP
    pop EBP
    mov EAX, res_base
    ret
    
_concatenate:
    push EBP
    mov EBP, ESP
    pushad
    
    mov ESI, [EBP+8]
    
    mov ECX, 0
    loop1:
    stosb
    cmp AL, 0
    je endLoop
    inc ECX
    jmp loop1
    endLoop:
    mov [res_conc], ECX
     
    popad
    mov ESP,EBP
    pop EBP
    mov EAX, [res_conc]
    ret    
    
 
    