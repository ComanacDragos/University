bits 32
global start


extern exit
import exit msvcrt.dll

segment data use32 class=data
    s DD 12345678h, 1A2C3C4Dh, 98FCDC76h
    len equ ($-s)/4
    ten dd 10
    doi dd 2
    aux resb 10 
    d resb len
    
    
segment class use32 class=class

    start:
    mov ESI, s
    mov EDI, d
    mov ECX, len
    
    loop1:
        lodsd
        
        push ESI
        push EDI
        push ECX
        push EAX
        
     
        mov ECX, 0
        
        loop2:
           cmp EAX, 0
           je endLoop2
          
           mov EDX, 0
           div dword [ten]
           mov [aux+ECX], EDX ; aux[i] = n%10  
           
           inc ECX
        
        jmp loop2
        endLoop2:
        
        mov EAX,ECX
        mov EDX, 0
        div dword [doi]
        
        mov EDX, ECX
        mov ECX, EAX ; ECX = nr_cif/2, EDX = nr_cif
        ;dec ECX
        ;dec EDX
        
        loop3:
            mov AL, [aux+ECX-1]
            mov AH, [aux+EDX-1-ECX]
            
            cmp AL, AH
            jne not_palindrom
            
            
        endLoop3:
        loop loop3
        
        
        
        
    endLoop1:
    
    
    push dword 0
    call [exit]