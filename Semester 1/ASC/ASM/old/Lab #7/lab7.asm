bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    
    s1 dd '1', '2', '3'
    len1 equ ($-s1)/4
    s2 dd '9', '3', '4', '5', '6'
    len2 equ ($-s2)/4
    d dd 0 ; adresa sirului cel mai mare
    rem dd 0
    r times len2+len1 db 0 
    
segment code use32 class=code
    
    start:
    mov ECX, len1
    mov EDX, s2 + len2*4-4
    mov [d], EDX
    
    mov byte [rem], len2 - len1
   
    cmp ECX, len2
    jb l 
    mov ECX, len2
    mov EDX, s1 + (len1-1)*4
    mov [d], EDX 
    mov byte [rem], len1 - len2
   
    l:
    mov ESI, 0
    mov EDI, r
    loop1:
        mov EAX, [ESI+s1]
        mov EBX, [ESI+s2]
        cmp EAX, EBX
        ja label1
            mov EAX, EBX
        label1:
        sub EAX, '0'
        mov DL, 0
        biti:
        test eax, 1
        jz par
        inc DL
        par:
        shr EAX,1
        cmp EAX, 0 
        jne biti
        
        add ESI,4
        mov AL,DL
        stosb
        loop loop1
    
    mov ESI, [d]
    mov ECX, [rem]
 
    loop2:
        std
        lodsd 
        sub AL, '0'
        cld
        stosb
    loop loop2
    
    
    push dword 0
    call [exit]