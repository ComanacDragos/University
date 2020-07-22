bits 32
global start

extern exit
import exit msvcrt.dll


segment data use32 class=data
    s db `abc`
    len equ $-s
    d times len db 0
    
    
segment code use32 class=code
    start:

    mov ESI, s  ; store the offset of the souce string "s" into esi
    mov d, EDI  ; store the offset of the destination string "d" in EDI
    cld ;       DF = 0 (strings are parsed from left to right
    
    repeat:
        lodsb ; AL <- [ESI], ESI := ESI+1
        sub AL, 'a'-'A'
        stosb ; AL -> [EDI], EDI := EDI+1
        dec ECX
        cmp ECX, 0 ; loop repeat
        ja repeat

    
    push dword 0
    call [exit]
  