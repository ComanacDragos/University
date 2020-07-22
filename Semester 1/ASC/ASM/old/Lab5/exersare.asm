bits 32
global start

extern exit
import exit msvcrt.dll
 
segment data use32 class=data

    s dw 1432h, 8675h, 0ADBCh 
    len equ ($-s)/2
    aux resb 4
    d resd len
    
    
    ;1432h --> 01, 02, 30, 04
    
    
    ;AL = 32
    ;BL = F0
    ;and= 30 (03)
    
    ;01020304 --- 04 03 02 01

segment code use32 class=code
    start:
    
    mov ECX, len
    mov EDI, d
    mov ESI, s
    
    loop1:
        lodsw
      
        mov BL, 0Fh ; 0000 1111
        and BL, AL ; BL = 0000 nibble inf din al
        
        mov [aux], BL
        
        mov BL, 0F0h
        and BL, AL
        shr BL, 4
        
        mov [aux+1], BL
        
        mov BL, 0Fh
        and BL, AH
        
        mov [aux+2], BL
        
        mov BL, 0F0h
        and BL, AH
        shr BL, 4
        
        mov [aux+3], BL
        
        mov EAX, 0 ; i = 0
        loop2:
            cmp EAX, 3
            je endLoop2
            
            mov EBX, EAX
            loop3:
            inc EBX ; j = i+1
            
            cmp EBX, 4
            je endLoop3
            
            mov DL, [aux+EAX] ; aux[i]
            mov DH, [aux+EBX] ; aux[j]
            
            cmp DL, DH
            ja endCMP
            
            mov [aux+EAX], DH
            mov [aux+EBX], DL
            endCMP:
            
            jmp loop3
            endLoop3:
            
        inc EAX
        jmp loop2
        endLoop2:
        
    mov EBX, ESI
    mov ESI, aux
    lodsd
    stosd
    mov ESI, EBX
    
    loop loop1
        
        
    
    push dword 0
    call [exit]
    
    
    
    bubbleSort:
    
        mov EDX, 0 ; <=> ok
        
        loop2: ;(while ok == 0)
            cmp EDX, 1
            je endLoop2
            
            mov EDX, 1
            mov EBX, 0 ; i=0
            loop3: ; while(ebx ==3) 
                cmp EBX, 3 ; if (i<n-1)
                je endLoop3
                
                mov AL, [aux+EBX] ; aux[i]
                mov AH, [aux+EBX+1]; aux[i+1]
                
                cmp AL, AH ; if(aux[i] > aux[i+1])
                ja endCMP
                
                mov [aux+EBX+1], AL ; swap(aux[i], aux[i+1])
                mov [aux+EBX], AH
                mov EDX, 0 ; ok = 0 
            
            endCMP:
            inc EBX
            jmp loop3
            endLoop3:

        jmp loop2
        endLoop2:    