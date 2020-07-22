%ifndef _STRING_ASM_
%define _STRING_ASM_

    
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


%endif