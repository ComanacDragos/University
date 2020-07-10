bits 32
global _concatenat

segment data public data use32
    res_con db 10

segment code public code use32
_concatenat:
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
    mov EAX, [res_con]
    ret