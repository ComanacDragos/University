bits 32
global start

extern exit, scanf
import exit msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data

    v resd 128 ; reserves memory
    fmt db "%d",0

segment code use32 class=code

  start:
    
    mov EBX, v 
    mov ECX, 128
    
    b:
    
        push ECX
        push EBX
        push fmt
        
        call [scanf]
        
        add ESP, 2*4
        
        pop ECX
        add EBX, 4
        
        cmp EAX, 0 
        
        loop nnz b ; loop ne
    
    push dword 0
    call [exit]