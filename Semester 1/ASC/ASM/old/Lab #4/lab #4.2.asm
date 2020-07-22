bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 10110011b
    b db 01110001b
    c db 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
    mov AL,[b]
    and AL,11100000b 
    shr AL, 5
    mov [c],AL ; c = 00000011
    
    
    
    mov BX,[b]
    and BX, 0001110000000000b
    
    shr BX,10
    
    mov word [c],BX
   
    or word [c], 0000000001111000b
    
    mov AX,[a]
    and AX, 0000000000011110b
    shl AX,6
    and word [c], 1111100001111111b
    or word [c], AX
    
    mov BX,[b]
    not BX
    and BX,0000111000000000b
    mov CL,4
    shl BX,CL
    or word [c], BX
    
    
        ; exit(0)
    push    dword 0      ; push the parameter for exit onto the stack
    call    [exit]       ; call exit to terminate the program
