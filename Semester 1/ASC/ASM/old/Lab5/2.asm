bits 32
global start


extern exit
import exit msvcrt.dll

segment data

segment code

   start:
   mov EAX, 1
   neg EAX
   
   mov EBX, 1
   not EBX
   
   
   push dword 0
   call [exit]