bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; Se da un sir de dublucuvinte. Sa se obtina sirul format din octetii superiori ai 
; cuvitelor superioare din elementele sirului de dublucuvinte care sunt divizibili cu 3.
; Exemplu:

; Se da sirul de dublucuvinte:
; s DD 12345678h, 1A2B3C4Dh, FE98DC76h
; Sa se obtina sirul
; d DB 12h.
segment data use32 class=data
    
        S dd 12345678h, 1A2B3C4Dh, 0FE98DC76h
        len equ ($-S)/4
        trei dd 3
        D resb len

; our code starts here
segment code use32 class=code
    start:
        
        mov ecx, len
        mov esi, S
        mov edi, D
        
        loop1:
        
        lodsd ; eax = esi, esi+=4
        cdq ; edx:eax = esi
         
        mov ebx, eax ; ebx = eax
        
        idiv dword [trei] ; edx = edx:eax % 3
        
        cmp edx, 0
        jne endloop
        
        shr ebx, 24
        mov eax, ebx
        stosb ; edi = al, edi+=1
        
        endloop:
        loop loop1
        
        
        
        
        
         
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
