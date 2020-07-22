bits 32
global _conc

segment data public data use32
  
    res_conc resb 200
    
segment code public code use32
_conc:
    
    push EBP
    mov EBP, ESP
    pushad
    
    
    mov ESI, [EBP+8]
    mov ECX, [EBP+12]
    mov EDI, res_conc
    
    loop1:
        lodsb
        stosb
    loop loop1
    
    mov ESI, [EBP+16]
    mov ECX, [EBP+20]
    
    loop2:
        lodsb
        stosb
    loop loop2
    
    loop3:
        cmp dword [EDI], 0
        je endLoop3
        
        mov dword [EDI], 0
        inc EDI
        jmp loop3

    endLoop3:
    
    popad
    mov ESP,EBP
    pop EBP
    mov EAX, res_conc
    ret

    