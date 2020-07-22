bits 32
global _strcpy


segment code public code use32
_strcpy:
    
    push EBP
    mov EBP, ESP
    pushad
    
    mov ESI, [EBP+12]
    mov EDI, [EBP+8]
    
    loop1:
        lodsb
        cmp AL, 0
        je endLoop1
        stosb
        jmp loop1
    endLoop1:
    
    mov byte [EDI], 0
    
    popad
    mov ESP,EBP
    pop EBP
    mov EAX, 0
    ret
       
    
    