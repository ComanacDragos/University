bits 32
global start

extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data

    a1 db "abcd"
    len1 equ $-a1
    a2 db "efgh"
    len2 equ $-a2
    res resb len1+len2
    
    
segment text use32 class=code

    start:
    mov ESI, a1
    mov EDI, res
    mov ECX, len1
    
    l1:
    lodsb
    stosb ; movsb
    loop l1
    
    mov ECX, len2
    
    l2:
    movsb
    loop l2
    
    
    push dword 0
    call [exit]
    
    