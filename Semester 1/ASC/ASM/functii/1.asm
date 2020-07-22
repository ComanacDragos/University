bits 32
global start

extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll


segment data

    msg1 db "Give number: ", 0
    msg2 db "The requied value is: %d", 0
    
    f_d db "%d", 0
    
    
    a resw 1
    m resb 1
    n resb 1
    
segment code

    start:
    push msg1
    call [printf]
    add ESP, 4*1
    
    push a
    push f_d
    call [scanf]
    
    push msg1
    call [printf]
    add ESP, 4*1
    
    push m
    push f_d
    call [scanf]
    
    push msg1
    call [printf]
    add ESP, 4*1
    
    push n
    push f_d
    call [scanf]
        

    mov AX, [a]
    mov CL, [n]
    shr AX, CL ; AX/2 

    mov BX, 0
    
    mov ECX, 0
    mov CL, [m]
    sub CL, byte [n]
    inc CL
    loop1: 
        shl BX, 1
        add BX, 1
        
        ;1: BX = 1
        ;2: BX = 10 -> BX = 11
        ;3: BX = 110 -> BX = 111
        ; ... 
    loop loop1
    
    and AX, BX
    
    cwd
    
    push EAX
    push msg2
    call [printf]
    add ESP, 4*2
    
    
    ; 148 = 1001 0100 
    
    
    
    
    
    
    push dword 0 
    call [exit]