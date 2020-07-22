bits 32
global string_to_number

segment data use32 class=data public
    doi db 2

segment code use32 class=code public

    string_to_number:
   
    mov EDX, [ESP+4]
    mov ECX, [ESP+8]
    
    lea EDX, [EDX+ECX-1]
    
    mov AL, 1
    mov BL, 0
    
    l:
        cmp byte [EDX], '0'
        je endl
        add BL, AL
       
        endl:
        mul byte [doi]
        dec EDX
        loop l
    
    mov EAX, 0
    mov AL, BL
    ret