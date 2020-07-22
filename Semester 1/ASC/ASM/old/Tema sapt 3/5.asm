bits 32
global start 
extern exit
import exit msvcrt.dll

segment data use32 class=data

    a db 2
    b db 3
    c db 4
    d db 7
    e dw 7
    f dw 9
    g dw 7
    h dw 8
    
segment code use32 class=code
    ; f*(e-2)/[3*(d-5)]
    start:
    mov AL,3 ; AL=3
    mov BL,[d] ; BL=d=7
    sub BL,5 ; BL=d-5=2
    mul byte BL ; AX=AL*BL=3*2=6
    mov BX,AX ; BX=AX=6
    mov AX,[e] ; AX=e=7
    sub AX,2 ; AX=e-2=5
    mul word [f] ; DX:AX=f*(e-2)=9*5=45
    div word BX ; AX=DX:AX/BX=45/6=7  DX=DX:AX%BX=45%3=3
    
push dword 0
call [exit]