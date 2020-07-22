bits 32
global _interleave

segment data public data use32
    res resb 200
    s1 db "abc"
    s2 db "defsd"

segment code public code use32
   
_interleave:
    push EBP
    mov EBP, ESP
    pushad
    
    
    mov EAX, [EBP+8]
    mov EBX, [EBP+12]
    mov ECX, [EBP+16]
    mov EDI, res
   
    
    
    loop1:
        mov DL, byte [EAX]
        mov [EDI], DL
        inc EDI
        mov DL, byte [EBX]
        mov byte [EDI], DL
        inc EDI
        inc EAX
        inc EBX
    loop loop1
     
    
    popad
    mov ESP,EBP
    pop EBP
    mov EAX, res
    ret
    