bits 32

global start

extern exit, scanf, printf

import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

%include "modul.asm" ; concatenare

; 6. Se citesc trei siruri de caractere. Sa se determine si sa se afiseze rezultatul concatenarii lor.
segment data
        
        s1 resb 10
        s2 resb 10
        s3 resb 10
        format db "%s %s %s", 0
        format1 db"%s", 0
        
        rez resb 200

segment code

    start:
        
        push dword s3
        push dword s2
        push dword s1
        push dword format
        call [scanf]
        add esp, 4*4
        
        push rez ; ESP + 16
        push s3 ; ESP + 12
        push s2 ; ESP +8 
        push s1 ; ESP + 4 = s1
        call concatenare ; ESP = adresa urmatoarei linii
        add esp, 4*4
        
        push rez
        push format1
        call [printf]
        add esp, 4*2

        jmp $
        
        push 0
        call [exit]
        
       
   
