bits 32
global start

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    x dq 012CAFCAFEA33h
    s times 16 db 0, 0
    digits db '0123456789ABCDEF'
    hexa dd 16
    substring db 'CAFEA'
    len equ $-substring
    mesYes db 'yes', 10, 0
    mesNo db 'No', 10, 0
    

segment code use32 class=code
    ; sa se caute string ul cafea in reprezentarea hexa a quadwordului (se da)
    searchString:
        ; functia cauta substringul cu offset in edi in stringul cu offset in esi
        ; substringul are lungimea in eax iar stringul este sir ASCIIZ
        cld
        push EDI
        mov EBX, EAX
        mov AL, 0 ; functia intoarce in AL valoarea 0 daca nu a gasit substringuri
        
        repeat:
            pop EDI
            push EDI
            push ESI ; save current offset in string
            mov ECX, EBX
            repe cmpsb ; repeat cmpsb while equal ([ESI] == [EDI]) or ECX times
            
            jne next
            mov al,1 ; am gasit substringul
            pop ESI ; nu mai avem nevoie de ESI
            pop EDI
            
            jmp endFunction
            next:
                pop ESI
                pop EDI
                inc ESI
                push EDI
                cmp byte [ESI], 0
                jne repeat
       
                pop EDI
                endFunction:
                ret
    
    
    start:
        std
        mov EDI, s+15
        ; obtinem intai cifrele hexa ale dwordului low al lui x
        mov EAX, [x]
        repeat1:
            mov EDX, 0
            div dword [hexa]
            ; restul e in EDX (mai exact in DL)
            ; obtinem codul ascii al cifrei
            mov ECX, EAX; save EAX
            mov AL, DL
            mov EBX, digits
            xlat ; codul ascii al cifrei este in al
            stosb
            mov EAX, ECX ; restore EAX
            
            cmp EAX, 0
            ja repeat1
            
        ; obtinem cifrele hexa ale dwordului high
        mov EAX, [x+4]
        repeat2:
            mov EDX, 0
            div dword [hexa]
            ; restul e in EDX (mai exact in DL)
            ; obtinem codul ascii al cifrei
            mov ECX, EAX; save EAX
            mov AL, DL
            mov EBX, digits
            xlat ; codul ascii al cifrei este in al
            stosb
            mov EAX, ECX ; restore EAX
            
            cmp EAX, 0
            ja repeat2
        
        ; apelam functia searchString
        mov ESI, s
        mov EDI, substring
        mov EAX, len
        call searchString
        cmp AL, 1
        je found
        ; not found
        push mesNo
        call [printf]
        add ESP, 1*4
        jmp theend
        
        found:
            push mesYes
            call [printf]
            add ESP, 1*4
        
    theend:
        
    push dword 0
    call [exit]