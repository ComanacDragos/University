bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data

    s1 db 'abacad'
    lens1 equ $-s1
    s2 db 'cafegd'
    lens2 equ $-s2
    result times lens1+lens2 db 0

segment code use32 class=code
;1. se dau 2 stringuri. sa se obtina caracterele comune ale celor 2 stringuri
    start:
        cld
        mov EBX, 0; the lenght of string result
        
        mov ESI, s1
        mov ECX, lens1
        
        repeat:
            mov EDI, s2
            push ECX
            mov ECX, lens2
            lodsb
            repne scasb ; executa scasb cat timp al diferit de byte ul de la offset ul edi, de max ecx ori
            
            jnz not_found ; nu am gasit pe al in sirul s2
            
            ; verificam sa nu fie dublura in result
            
            cmp EBX, 0
            je add_to_string
            mov EDI, result
            mov ECX, EBX
            repne scasb
            
            jz no_add
            ; adaugam pe al in result
            add_to_string:
            mov [result+EBX], AL
            inc EBX
            
            not_found:
            no_add:
            pop ECX
            loop repeat
            
            
    push dword 0
    call [exit]