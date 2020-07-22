bits 32
global start

extern exit, scanf
import exit msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data:
    n resd 1
    f db "%d", 0

segment code use32 class=code:
    start:
    push n
    push f
    call [scanf]
    
    
    push dword 0
    call [exit]