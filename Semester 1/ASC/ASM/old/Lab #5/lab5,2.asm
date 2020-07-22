bits 32
global start

extern exit, scanf
import exit msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data

    a db 1,3,-4,-6
    len equ $-a
    r times len db 0
    
    
segment code use32 class=code

    start:
    
    mov ECX, len
    mov ESI, a
    mov EDI, r
    
    l:
    cmp byte [esi], 0
    jge end
    test byte [esi], 1
    jnz end
    
    mov AL,[esi]
    mov [edi], AL
    
    
    inc edi
    
    end:
    inc esi
    loop l 
    
    
    push dword 0
    call [exit]