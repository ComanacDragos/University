bits 32
global start 

extern exit
import exit msvcrt.dll

segment data use32 class=data

    s db 1,2,3,4
    len equ $-s
    d times len db 0

segment code use32 class=code
  
    start:
    ; being given a string of bytes obtain the mirror image of the string
    ; the source string "s" will be parsed from left to right, so we store the offset of the first byte of "s" into ESI
    mov ESI, s
    ; the destination string "d" will be parsed from right to left, so we store the offset of the last byte from string "d" into EDI
    mov EDI, d+len-1
    mov ECX, len
    
    repeat:
        cld ; DF = 0 strings are parsed from left to right
        lodsb ; AL = [ESI], ESI = ESI+1
        std ; DF = 1 strings are parsed from right to left
        stosb ; AL -> [EDI], EDI := EDI-1
    loop repeat
   
    push dword 0
    call [exit]
