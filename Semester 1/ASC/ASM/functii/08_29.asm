bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; Se citesc de la tastatura trei numere a, m si n (a: word, 0 <= m, n <= 15, m > n). Sa se izoleze bitii de la m-n ai lui a si sa se afiseze numarul intreg reprezentat de acesti bitii in baza 10.
segment data use32 class=data
    
    mesaj db "dati numar: ", 0
    mesaj2 db "nr este: %d", 0 
    
    format db "%d", 0
    
    
    a resd 1
    m resd 1 ; citesti  m ->> citesti 
    n resd 1
    
    
    ; scanf(format,%d)
    

; our code starts here
segment code use32 class=code
    start:
        push mesaj
        call [printf]
        add ESP, 4*1
        
        push a
        push format
        call [scanf]
        ;add ESP, 4*2
       
        push mesaj
        call [printf]
        add ESP, 4*1
        
        push m
        push format
        call [scanf]
        ;add ESP, 4*2
        
        push mesaj
        call [printf]
        add ESP, 4*1
        
        push n
        push format
        call [scanf]
        ;add ESP, 4*2
    
    
    
    
    
    
    
    
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
