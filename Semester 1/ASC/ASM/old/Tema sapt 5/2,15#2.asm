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
    ;x-(a*b*25+c*3)/(a+b)+e - signed representation
        start:
    
    mov AL,[a] ; AL=a
    imul byte [b] ; AX=a*b
    mov BX,25 ; BX=25
    imul word BX ; DX:AX=a*b*25
    mov BX,AX ; DX:BX=a*b*25
    
    mov AL,3 ; AL=3
    imul byte [c] ; AX=3*c
    mov CX,0 ; CX:AX=c*3
    
    add BX,AX
    adc DX,CX ; DX:BX=a*b*25+c*3
    
    mov AL,[a] ; AL=a
    add AL,[b] ; AL=a+b
    
    cbw ; AX=a+b
    
    mov CX,AX ; CX=a+b
    mov AX,BX ; DX:AX=a*b*25+c*3
    idiv CX ; AX=(a*b*25+c*3)/(a+b)
    
    cwde ; EAX=(a*b*25+c*3)/(a+b)
    cdq ; EDX:EAX=(a*b*25+c*3)/(a+b)
    
    mov EBX, dword [x]
    mov ECX, dword [x+4] ; ECX:EBX=x
    
    sub EBX,EAX
    sbb ECX,EDX ; ECX:EBX=x-(a*b*25+c*3)/(a+b)
    
    mov EAX,[e]
    cdq ; EDX:EAX=e
    
    add EBX,EAX
    adc ECX,EDX ; ECX:EBX=x-(a*b*25+c*3)/(a+b)+e
    
    
    
    
    
    push dword 0
    call [exit]