; citire siruri
%ifndef _MODUL_ASM_
%define _MODUL_ASM_
 
concatenare:

        ;mov ecx, [esp+12]
        ;mov edx, [esp+16]
        
        mov edi, [esp+16] ; rez
        
        ;mov esi, [esp+4]
        
        mov ecx, 1
        
        loop2:
        
            cmp ecx, 4
            je endloop2
            
            mov esi, [esp+4*ecx] ; ia fiecare sir
            
            loop1:
                
                lodsb
                
                cmp al, 0
                je endloop1
                
                stosb
                
            jmp loop1
            
        endloop1:
        
        inc ecx
        jmp loop2
       
        endloop2:

        ret ; jmp [ESP]    
%endif
