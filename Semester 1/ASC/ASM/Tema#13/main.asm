bits 32
global start

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

%include "string_to_number.asm"

segment data use32 class=data

    string db '10100111b', '01100011b', '110b', '101011b', 0
    f db "%X", 10, 0
    doi db 2
    new_string resb 100
    
segment code use32 class=code

    start:

    mov ESI, string
    mov EDI, new_string
    
    loop1:

        cmp byte [ESI], 0
        je endLoop1
        
        mov EDX, ESI
        
        loop2:
            lodsb
            cmp AL, 'b'
            je endLoop2
        jmp loop2
        endLoop2:
        
        mov ECX, ESI
        sub ECX, EDX
        dec ECX
        
        push ECX
        push EDX
        call string_to_number
        add ESP, 4*2
        
        stosb
        
        jmp loop1
        endLoop1:
        
      
            
        mov ESI, new_string
        
        loop3:
            cmp byte [ESI], 0
            je theEnd
            mov EAX, 0
            lodsb
            
            push EAX
            push f
            call [printf]
            add ESP, 4*2
            jmp loop3
    
    theEnd:
    push dword 0
    call [exit]

            
  