;caracterul special cu frecventa cea mai mare
bits 32
global start

extern exit, fopen, fread, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    format db "%s", 0
    filename db "input.txt", 0
    descriptor resd 1
    acces_mode db "r", 0
    maxChar dd 0
    maxVal db 0
    
 
    buffer resb 100
    frecventa times 256 dw 0
    

segment code use32 class=data

    start:
    
    push acces_mode
    push filename
    call [fopen]
    add ESP, 4*2
    
    mov [descriptor], EAX
    
    citire:
        push dword [descriptor]
        push 100
        push 1
        push buffer
        call [fread]
        add ESP, 4*4
        
        cmp EAX, 0
        je endcitire
        
        mov ECX, EAX
        mov ESI, buffer
        parcurgere:
            lodsb
            
            cmp AL, '0'
            jb notDigit
            
            cmp AL, '9'
            ja notDigit
            
            jmp endParcurgere
            notDigit:
            
            cmp AL, 'A'
            jb notUpper
            
            cmp AL, 'Z'
            ja notUpper
            
            jmp endParcurgere
            notUpper:
            
            cmp AL, 'a'
            jb notLower
            
            cmp AL, 'z'
            ja notLower
            
            jmp endParcurgere
            notLower:
            
            mov EDX, 0
            mov DL, AL
            mov AL, [frecventa+EDX]
            inc AL
            mov [frecventa+EDX], AL
         
         endParcurgere:
         loop parcurgere
         
     jmp citire   
    endcitire:
    
    mov ESI, frecventa
    mov ECX, 256
    
    loop1:
        lodsb
        
        cmp AL, [maxVal]
        jb endLoop1
        mov [maxVal], AL
        mov EBX, ESI
        dec EBX
        mov [maxChar], EBX
        
    endLoop1:
    loop loop1
    mov EAX, frecventa
    sub [maxChar], EAX
    
    push maxChar
    push format
    call [printf]
    add ESP, 4*2
   
    
    push dword 0
    call [exit]
