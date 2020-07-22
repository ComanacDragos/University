bits 32
global _str_len

segment data public data use32
    res_str_len resd 1

segment code public code use32

_str_len:

    push EBP
    mov EBP, ESP
    pushad

    mov ESI, [EBP+8]
    
    mov ECX, 0
    loop1:
    lodsb
    cmp AL, 0
    je endLoop
    inc ECX
    jmp loop1

    endLoop:
    mov [res_str_len], ECX
    popad
    mov ESP,EBP
    pop EBP
    mov EAX, [res_str_len]
    ret