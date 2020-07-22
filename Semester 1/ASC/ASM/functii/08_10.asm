bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, fopen, fprintf, printf, gets               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import scanf msvcrt.dll
import gets msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import printf msvcrt.dll

; 10. Sa se citeasca de la tastatura un nume de fisier si un text. Sa se creeze un fisier cu numele dat in directorul
; curent si sa se scrie textul in acel fisier. Observatii: Numele de fisier este de maxim 30 de caractere. Textul este
; de maxim 120 de caractere.
segment data use32 class=data
    
        format db "%s", 0
        descriptor dd 0
        mod_scriere db "w", 0
        
        msg1 db "nume fisier: ", 0
        msg2 db "text: ", 0
        
        max_len_f equ 30
        nume_fisier times max_len_f db 0
        ;nume_fisier resd 1
        max_len_t equ 120
        text times max_len_t db 0

; our code starts here
segment code use32 class=code
    start:
    
        ; printf
        push msg1
        call [printf]
        add esp, 4
        
        ; scanf(format1,nume_fisier)
        push nume_fisier
        call [gets]
        add esp, 8
        
        ; printf
        push msg2
        call [printf]
        add esp, 4
        
        ; scanf(format2,text)
        push text
        call [gets]
        add esp, 4
        
        ; fopen(nume_fisier,mod_scriere)
        push mod_scriere
        push nume_fisier
        call [fopen]
        add esp, 8
        
        mov [descriptor], eax
        
        mov esi, text
        
        
        ; fprintf(descriptor,format,text)
        push text
        push format
        push dword [descriptor]
        call [fprintf]
        add esp, 12
            
            
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
