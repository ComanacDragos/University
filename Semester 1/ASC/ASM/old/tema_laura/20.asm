bits 32
global start

extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    s1 dd 1,2,3, 0
    
    msg1 db "a= ", 0
    msg2 db "b= ", 0
    msg3 db "The sum of low bytes is: ", 0
    msg4 db 10, "The dif of high bytes is: ", 0
    
    f_x db "%x", 0
    ;a resd 1
    b resd 1
    
    a db 1
    db 4
    
segment code use32 class=code
    start:
    mov ax, [a+1]
   
    
    
    
    push msg1
    call [printf]
    add ESP, 4
    
    push a
    push f_x
    call [scanf]
    add ESP, 4*2
    
    push msg2
    call [printf]
    add ESP, 4
    
    push b
    push f_x
    call [scanf]
    add ESP, 4*2
    
    push msg3
    call [printf]
    add ESP, 4
    
    ;mov EAX, 0
    mov AX, [a]
    mov BX, [b]
    
    add AX, BX
    
    
    push EAX
    push f_x
    call [printf]
    add ESP, 4*2
    
    push msg4
    call [printf]
    add ESP,4
    
    ;mov EAX, 0
    mov AX, [a+2]
    mov BX, [b+2]
    
    sub AX, BX
    
    push EAX
    push f_x
    call [printf]
    add ESP, 4*2
    
    
    push dword 0
    call [exit]