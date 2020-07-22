bits 32
global start

extern exit, fprintf, scanf, fopen
import exit msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll



;f(a,b,c) ; push c
;push b
;push a

;pop a
;pop b
;pop c

segment data use32 class=data
   
   file db "file.txt", 0
   f_m db "w", 0 ; modul de scriere
   f_s db "%s", 0 
   f_s_fprintf db "%s", 10, 0
   d_f resd 1 ; descriptor de fisier
   
   s resb 100
   
   ; fopen(nume_fisier, mod_fisier)
   
segment code use32 class=code
    start:  
    
    push f_m
    push file
    call [fopen]
    add ESP, 4*2
    
    mov [d_f], EAX
    
    loop1:
        push s
        push f_s
        call [scanf]
        add ESP, 4*2
        
        mov AX, [s]
        cmp AX, '$'
        je endLoop1
        
        mov ESI, s
        loop2:
            lodsb
            cmp AL, 0
            je endLoop2
        
            cmp AL, '0'
            jb notDigit
            
            cmp AL, '9'
            ja notDigit
        
            push s
            push f_s_fprintf
            push dword [d_f] ; push d_f
            call [fprintf]
            add ESP, 4*3
            jmp endLoop2
            
        notDigit:
        jmp loop2
        endLoop2:
        
    jmp loop1
    endLoop1:
        
     
    push dword 0 
    call [exit]