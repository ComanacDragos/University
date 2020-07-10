bits 32
global _array_max

segment data public data use32
    mx dd 0

segment code public code use32
        
_array_max:
        push EBP
        mov EBP, ESP
        pushad
        
    
        mov ESI, [EBP+8]
        mov ECX, [EBP+12]
        
        lodsd
        mov [mx], EAX
        dec ECX
        
        loop1:
            lodsd
            cmp [mx], EAX
            jg endLoop
            mov [mx], EAX
            
            endLoop:
            loop loop1
        
        popad
        mov ESP, EBP
        pop EBP
        mov EAX, [mx]
        ret
        
        
        