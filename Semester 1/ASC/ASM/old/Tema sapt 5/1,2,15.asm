bits 32
global start
extern exit
import exit msvcrt.dll

segment data use32 class=data

    a db 20
    b dw 400
    c dd 1000
    d dq 4294
    
segment code use32 class=code
    ;d-(c+a+b+b+a)
    start:
    
    mov AL,[a] ; AL=a
    add AL,[a] ; AL=a+a
    cbw ; AX=a+a
    add AX,[b]  ; AX=b+a+a
    add AX,[b] ; AX=b+b+a+a
    cwde ; EAX=a+a+b+b
    add EAX,[c] ; EAX=a+a+c+b+b
    
    mov EBX,0 ; EBX:EAX=a+a+b+b+c
    
    mov ECX, dword [d]
    mov EDX, dword [d+4] ; EDX:ECX=d
    
    sub ECX,EAX
    sbb EDX,EBX
    push dword 0
    call [exit]
    
    