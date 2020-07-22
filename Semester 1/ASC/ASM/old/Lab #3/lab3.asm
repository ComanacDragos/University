bits 32
global start
extern exit
import exit msvcrt.dll

segment data use32 class=data

    a dd 10
    b db 8 
    c dw 4
    d db 1
    e dq 5
segment code use32 class=code
    start:
    ; a+b/c-d*2-e unsigned
    mov AL,[b]
    mov AH,0
    mov DX,0 ; DX:AX=0
    div word [c] ;AX=b/c ; DX=b%c
    mov BX,AX ; BX=b/c
    mov AL,2
    mul byte [d] ; AX=2*d
    sub BX,AX ; BX=b/c-d*2
    mov AX,0 ; AX:BX=BX
    add BX, word [a]
    adc AX, word [a+2] ; AX:BX=a+b/c-2*d
    mov DX,AX
    mov AX,BX
    push DX 
    push AX
    pop EAX
    mov EDX,0
    sub EAX, dword [e]
    sbb EDX, dword [e+4] 
    push dword 0
    call [exit]