bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...

; our code starts here
segment code use32 class=code
    start:
        ; ...
    

    a db 10
    b dw 40
; our code starts here
segment code use32 class=code
    start:
        mov AX,[b]
        div BYTE[a]  ; AL=b/a
        mov BL,2
        mul BL ; AX=b/a*2
        add AX,10 ; AX=b/a*2+10
        mul WORD[b] ; (32bits)DX:AX=(b/a*2+10)*b
        push DX
        push AX
        pop EBX ; EBX=(b/a*2+10)*b
        mov AX,15
        mul WORD[b] ;
        push DX
        push AX
        pop EAX ; EAX=b*15
        sub EDX,EAX ; EDX=(b/a*2+10)*b-b*15
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
