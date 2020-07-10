bits 32
global _base10Digits

;segment data public data use32
 ;   res_conc db 10

segment code public code use32
_base10Digits:
    push EBP
    mov EBP, ESP
    pushad
    
    
    popad
    mov ESP,EBP
    pop EBP
    mov EAX, 0
    ret
    
 
    