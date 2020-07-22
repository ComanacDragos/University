bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data:

    fmt db "ana %s are %d mere", 0
    f db "ana.txt", 0
    m db "w", 0
    n db "Pop", 0
    d_f dd -1
    mere dd 3
    f_str db "%s", 0
    f_d db "%d", 0
    

segment code use32 class=code:

    start:
    
    push dword n
    push f_str
    call [scanf]
    add esp, 4*2
    
    push mere
    push f_d
    call [scanf]
    add esp, 4*2
    
    
    push dword 0
    call [exit]