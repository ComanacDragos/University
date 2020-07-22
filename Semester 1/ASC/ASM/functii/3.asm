bits 32 
global start

extern exit, fopen, fread, fprintf, fclose
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll


segment data use32 class=data

    file db "fisier2.txt", 0
    mode db "a+", 0
    desc dd 0
    format db 10,"%d", 0
    medie dd 0
    numbers resb 100
    
    
    
segment code use32 class=data
    
    start:
    push mode
    push file
    call [fopen]
    mov [desc], EAX

    push dword [desc]
    push 100
    push 1
    push numbers
    call [fread]
    add esp, 4*4
    
    mov ESI, numbers
    mov ECX, 0
    loop1:
        lodsb
        cmp AL, 0
        je endloop1

        inc ECX
        
        cmp byte [ESI], '0'
        jne digit
        add dword [medie], 10
        inc ESI
        jmp loop1
        
        digit:
        sub AL, '0'
        cbw
        cwde
        add dword [medie], EAX
        inc ESI
        
    endLoop:    
    jmp loop1
    endloop1:
    
    mov EAX, [medie]
    mov EDX, 0
    div ECX
    
    add EDX, EDX
    cmp EDX, ECX ; 2r nr <=> r< nr/2
    jl no_rounding
    inc EAX
    
    no_rounding:

    
    push EAX
    push format
    push dword [desc]
    call [fprintf]
    add esp, 4*3
    
    push dword [desc]
    call [fclose]
    
    push dword 0
    call [exit]