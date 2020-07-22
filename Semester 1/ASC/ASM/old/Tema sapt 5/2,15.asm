bits 32
global start
extern exit
import exit msvcrt.dll

segment data use32 class=data

    a db 1
    b db 2
    c db 3
    e dd 10
    x dq 22
  
segment code use32 class=code
    ;x-(a*b*25+c*3)/(a+b)+e - unsigned representation
        start:
    
    mov AL,[a] ; AL=a
    mul byte [b] ; AX=a*b
    mov BX,25 ; BX=25
    mul word BX ; DX:AX=a*b*25
    mov BX,AX ; DX:BX=a*b*25
    
    mov AL,3 ; AL=3
    mul byte [c] ; AX=3*c
    mov CX,0 ; CX:AX=c*3
    
    add BX,AX
    adc DX,CX ; DX:BX=a*b*25+c*3
    
    mov AX,BX ; DX:AX=a*b*25+c*3
    
    mov BL,[a] ; BL=a
    add BL,[b] ; BL=a+b
    mov BH,0 ; BX=a+b
    
    div BX ; AX=(a*b*25+c*3)/(a+b) DX=(a*b*25+c*3)%(a+b)
    mov DX,0 ; DX:AX=(a*b*25+c*3)/(a+b)
    push DX
    push AX
    pop EAX ; EAX=(a*b*25+c*3)/(a+b)
    mov EDX,0 ; EDX:EAX=(a*b*25+c*3)/(a+b)
    
    mov EBX, dword [x]
    mov ECX, dword [x+4] ; ECX:EBX= x
    
    sub EBX,EAX
    sbb ECX,EDX ;  ECX:EBX=x-(a*b*25+c*3)/(a+b)
    
    mov EAX,[e] ; EAX=e
    mov EDX,0 ; EDX:EAX=e
    
    add EBX,EAX
    adc ECX,EDX ; ECX:EBX=x-(a*b*25+c*3)/(a+b)+e
    
    push dword 0
    call [exit]