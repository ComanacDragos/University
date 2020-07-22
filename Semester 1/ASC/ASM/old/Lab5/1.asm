bits 32
global start

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    format db "%s", 10, 0
    s db "y6u5798i"
    len equ $-s
    
    s2 db "bla1234bla"
    len2 equ $-s2
    res_base resb 200
    
segment code use32 class=code
get_base:
    mov ESI, [ESP+4]
    mov ECX, [ESP+8]
    mov EDI, res_base
    
    loop1:
        lodsb
        cmp AL, '0'
        jb endLoop
        
        cmp AL, '9'
        ja endLoop
        
        stosb
        
    endLoop:
    loop loop1
    
    
    loop2:
        cmp dword [EDI], 0
        je endLoop2
        
        mov dword [EDI], 0
        inc EDI
        jmp loop2

    endLoop2:
   ret
   
    start:
    
    push len
    push s
    call get_base
    add ESP, 4*2
    
    push res_base
    push format
    call [printf]
    add ESP, 4*2
    
   
    push len2
    push s2
    call get_base
    add ESP, 4*2
    
    push res_base
    push format
    call [printf]
    add ESP, 4*2
    
    push dword 0
    call [exit]

    
    
    mov ESI, [EBP+8]
    mov ECX, [EBP+12]
    mov EDI, res_base
    
    loop1:
        lodsb
        cmp AL, '0'
        jb endLoop
        
        cmp AL, '9'
        ja endLoop
        
        stosb
        
    endLoop:
    loop loop1

    loop2:
        cmp dword [EDI], 0
        je endLoop2
        
        mov dword [EDI], 0
        inc EDI
        jmp loop2

    endLoop2:
    
    

    TRASH
    
    
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
         
    
 
    
