bits 32
global start

extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data:

    message db "Give number: ", 0
    
    a resd 1
    b resd 1
    
    f_d db "%d", 0
    f_h db "The number in base 16 is %x", 0


segment code use32 class=code:
   ; Read two numbers a and b (in base 10) from the keyboard and calculate a+b. Display the result in base 16

    start:
    
    push message
    call [printf]
    add ESP, 4*1
    
    push a
    push f_d
    call [scanf]
    add ESP, 4*2
    
    
    push message
    call [printf]
    add ESP, 4*1
    
    push b
    push f_d
    call [scanf]
    add ESP, 4*2
    
    mov EAX, [a]
    add EAX, [b]
    
   
   
    
    push EAX
    push f_h
    call [printf]
    add ESP, 4*2
    
    
    push dword 0
    call [exit]