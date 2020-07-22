bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data

    s dw 2345h, 0a5h, 368h, 3990h
    len1 equ ($-s)/2 ; the lenght of s in words i.e. (in other words) 4
    t dw 4h, 2655h, 10
    len2 equ ($-t)/2 ; the lenght of t in words i.e. 3
    r times len1+len2 db 0
    
segment code use32 class=code
    ; 2 strings of words are given; concatenate the string of low bytes of the words from the first string to the string of high bytes of the words from the second string
    ; the resulted string of bytes should be sorted in ascending order in the signed interpretation
    start:
    
    ; store the low bytes of the words from string s into r
    mov ESI, s
    mov EDI, r
    mov ECX, len1
    
    cld
    
    repeat:
        lodsw ; AX <- [ESI] , ESI:= ESI+2
              ; the low byte of the current word from "S" is in AL
        stosb ; AL -> [EDI], EDI = EDI+1
    loop repeat
    
    ; store the high byte of the words from string t into r
    mov ESI, t
    mov ECX, len2
    repeat1:
        lodsw ; AX <- [ESI], ESI := ESI+2
              ; the high byte is in AH
        mov AL, AH
        stosb ; AL -> [EDI], EDI := EDI+1
    
    loop repeat1
    
    ; sort string r in ascending order in the signed interpretation
    
    mov DX, 1 ; DX=1 string is not sorted
    
    repeat2:
        cmp DX, 0
        je theend ; if DX == 0 the string is sorted so we should jump to the end of the program
        mov DX, 0 ; string is sorted
        
        mov ESI, r
        mov ECX, len1+len2
        repeat3:
            mov AL, [ESI]
            cmp AL, [ESI+1]
            jle next
            mov AH, [ESI+1]
            mov [ESI], AH
            mov [ESI+1], AL
            mov DX, 1 ; the string is not sorted
        
            next:
                inc ESI
                loop repeat3
                jmp repeat2
                
    theend:
       
        push dword 0
        call [exit]