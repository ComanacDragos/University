bits 32
global start

extern exit, scanf
import exit msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data:
   

segment code use32 class=code:
    start:

    
    push dword 0
    call [exit]