bits 32
global start

extern exit, fprintf, scanf, fopen, fclose
import exit msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    file db "file.txt", 0
    desc dd 0
    mode db "w", 0
    doi dd 2
    
    
    format db "%d", 0
    nr dd 0
    f_format db "%d ", 0

segment code use32 class=code
;R1. Sa se citeasca de la tastatura mai multe numere (naturale)intregi pana la citirea valorii 0.
; Sa se scrie intr-un fisier, separate de spatii, doar acele 
;numere negative care au numar impar de biti (cu valoarea 1).
    start:
    
    push mode
    push file
    call [fopen]
    add esp, 8
    mov [desc], EAX
    
    loop1:
        push nr
        push format
        call [scanf]
        add esp, 8
        
        mov EAX, [nr]
        cmp EAX, 0
        je endLoop1
        
        cmp EAX, 0
        jg endLoop
        
        mov EBX, 0
        loop2:
            cmp EAX, 0
            je endLoop2
            
            shr EAX, 1
            adc EBX, 0
        
        jmp loop2
        endLoop2:
        
        mov EAX, EBX
        mov EDX, 0
        
        div dword [doi]
        
        cmp EDX, 0
        je endLoop
        
        push dword [nr]
        push f_format
        push dword [desc]
        call [fprintf]
        add esp,12
        
    endLoop:
    jmp loop1
    endLoop1:

    push dword [desc]
    call [fclose]
    add esp,4
    
    
    push dword 0
    call [exit]