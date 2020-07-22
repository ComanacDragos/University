bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data

    s1 db '+', '4', '2', 'a', '8', '4', 'X', '5'
    len1 equ $-s1
    s2 db 'a', '4', '5'
    len2 equ $-s2
    s3 times len1 db 0

segment code use32 class=code
;Two character strings S1 and S2 are given.
;Obtain the string D by concatenating the elements found on the positions multiple of 3 from S1 and the elements of S2 in reverse order.
    start:
    
    mov AX, len1
    mov DX, 0
    mov BX, 3
    div BX ; DX = len1%3 ; AX = len1/3
    
    mov CX, AX
    inc CX
    
    mov ESI, s1
    mov EDI, s3
    
    loop1:
        mov AL, [ESI]
        mov [EDI], AL
        inc EDI
        
        mov BL, 3
        loop2:
            inc ESI
            dec Bl
            cmp BL, 0
            ja loop2
        
        dec CX
        cmp CX, 0
        ja loop1
        
    mov ECX, len2
    
    mov ESI, s2
    add ESI, ECX
    dec ESI
    
    loop3:
        mov AL, [ESI]
        mov [EDI], AL
        inc EDI
        
        dec ESI
        dec ECX
        
        cmp ECX,0
        ja loop3
        
           
   
    push dword 0
    call [exit]
    
    
    
    
    
    
    
    
    
    
    
    
    mov byte [rem], len2 - len1
    
    mov ESI, [d]
    mov EDX, [ESI]
    
    cmp ECX, len2
    jb l 
    mov ECX, len2
    ;mov dword d, s1 + len1-1
    mov byte [rem], len1 - len2
   
    l:
    mov EDX, [d]
  
    loop1:
        mov EAX, [ESI+s1]
        mov EBX, [ESI+s2]
        cmp EAX, EBX
        ja label1
            mov EAX, EBX
        label1:
        mov EDX, 0
        biti:
        
        test eax, 1
        jz par
        inc edx
        par:
        shr EAX,1
        cmp EAX, 0 
        je biti
        
        add ESI,4
        mov AL,DL
        stosb
        loop loop1
        
        
     
            
            
        
        
        
            
    ;theend:
    