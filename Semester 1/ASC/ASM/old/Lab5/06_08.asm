bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; 8. Se da un sir de dublucuvinte. Sa se obtina sirul format din octetii inferiori ai 
; cuvintelor superioare din elementele sirului de dublucuvinte care sunt palindrom in scrierea in baza 10.
; Exemplu:

; Se da sirul de dublucuvinte:
; s DD 12345678h, 1A2C3C4Dh, 98FCDC76h
; Sa se obtina sirul
; d DB 2Ch, FCh.
segment data use32 class=data
    
    s dd 12D591h, 98FCDC76h, 69201CBh
    len equ ($-s)/4
    zece dd 10
    doi dd 2
    
    d resb len
    aux resb 10

; our code starts here
segment code use32 class=code
    start:
        
        mov esi, s
        mov edi, d
        mov ecx, len
        
        loop1:
        
            lodsd ; eax = esi; esi+4
        
            push esi
            push ecx
            push edi 
            push eax 
            
            mov ecx, 0
            
            loop2: ; obtinem dublucuvantul in baza 10
             cmp eax, 0 ; eax = esi = dublucuvantul din sir
             je endloop2
             
             mov edx, 0 ; edx:eax = esi = dublucuvantul din sir
             
             div dword[zece] ; eax = esi/10 , edx = esi % 10
             mov [aux+ecx], edx ; aux = edx = esi % 10
             inc ecx
             
             jmp loop2
             
            ; aux contine cifrele in baza 10 a dublucuvantului din sir
            
            endloop2:
            
            ; initializam registrii pentru parcurgerea dublucuvantului
            
            mov eax, ecx ; eax = lungime dublucuvant (in baza 10)
            mov edx, 0 ; edx:eax = lungime dublucuvant
            
            div dword [doi] ; eax = edx:eax / 2 si edx = edx:eax % 2
            ; eax = lungime dublucuvant (in baza 10) / 2
            
            mov edx, ecx ; edx = lungime dublucuvant (in baza 10)
            
            mov ecx, eax ; ecx = lungime dublucuvant (in baza 10) / 2
            
            dec ecx ; ecx = lungime / 2 - 1 
            dec edx ; edx = lungime - 1
            
            mov ebx, 0 ; contor
            
            
            loop3: ; verificam daca dublucuvantul este palindrom
                
                cmp ebx, ecx ; ebx <= ecx
                jg endloop3
                
                mov al, [aux+ebx]
                push edx
                sub edx, ebx
                mov ah, [aux+edx]
                pop edx
                
                cmp al, ah
                jne not_palindrom ; nu e palindrom
                
                inc ebx
                
            jmp loop3
            
            
            endloop3: ; este palindrom
            
            pop eax ; eax = dublucuvant
            
            shr eax, 16
            and ax, 00FFh ; al
            
            
            pop edi
            
            stosb ; edi = al , edi+=1
            
            push edi
            push eax
            
            ;jmp pal

            not_palindrom:
            
            ;inc edi
            
            ;pal:
            pop eax
            pop edi
            pop ecx
            pop esi

        loop loop1
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
