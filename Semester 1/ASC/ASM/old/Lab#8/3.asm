bits 32

global start
extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
format db "%d", 10, 0
temp dw 0
a dq 0
b dq 0
segment code use32 class=code

start:

push a
push format
call [scanf]
push b
push format
call [scanf]
push dword [a]
push dword format
call [printf]
add esp, 4*3
push dword [b]
push dword format
call [printf]
add esp, 4*3

push dword 0
call [exit]