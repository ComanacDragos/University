bits 32
global start
extern exit
import exit msvcrt.dll

segment data use32 class=data

    a db 50
    b dw 100
    c dd 57
    d dq 171
   
segment code use32 class=code
    ; a+b-c+(d-a) - unsigned representation
    start:
    mov CL,[d]
    mov CH,0 ; CX=d
    mov DX,0 ; DX:CX=d
    push DX
    push CX
    pop ECX ; ECX=d
    mov EDX,0 ; EDX:ECX=d
    
    mov AL,[a] ; AL=a
    mov AH,0 ; AX=a
    mov BX,0 ; BX:AX=a
    push BX
    push AX
    pop EAX
    mov EBX,0 ; EBX:EAX=a
    
    sub ECX,EAX
    sbb EDX,EBX ; EDX:ECX=d-a
    
    mov AL,[a] ; AL=a
    mov AH,0 ; AX=a
    add AX,[b] ; AX=a+b
    mov DX,0 ; DX:AX=a+b
    sub AX,word [c] 
    sbb DX,word [c+2] ; DX:AX=a+b-c
    push DX
    push AX
    pop EAX ; EAX=a+b-c
    mov EBX,0 ; EBX:EAX=a+b-c
    
    add EAX,ECX 
    adc EBX,EDX ; EBX:EAX=a+b-c+(d-a)
    
    
    
    
    
    
    
     
    push dword 0
    call [exit]