bits 32
global start
extern exit
import exit msvcrt.dll

segment data use32 class=data

    a dd 3
    b db 8 
    c dw 4
    d db 1
    e dq 5
   
segment code use32 class=code
    ; a+b/c-d*2-e signed
    start:
    mov AL,[b]
    cbw ; AX=b
    cwd ; DX:AX=b
    idiv word [c] ; AX=b/c DX=a%c
    mov BX,AX ; BX=AX
    mov AL,2 ; AL=2
    imul byte [d] ; AX=2*d
    sub BX,AX ; BX=b/c-2*d
    mov AX,BX
    cwd ; DX:AX=b/c-2*d
    add AX, word [a]
    adc DX, word [a+2]
    push DX 
    push AX
    pop EAX
    cdq
    sub EAX, dword [e]
    sbb EDX, dword [e+4] 
    push dword 0
    call [exit]