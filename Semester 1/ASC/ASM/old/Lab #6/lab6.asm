bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data

    s dq 00123110110abcb0h
    l equ ($-s)/8
    opt db 8
    zece dd 10
    
segment code use32 class=code

    start:
    
    ; s: DS:ESI
    ; d: ES:EDI
    ; DF = 0 ->
    ; DF = 1 <-
    ; ECX, CX
    ;   LODSB AL<- DS:ESI, ESI++ if df = 0 ; ESI-- if df =1
       ; LODSW AX... ESi+=2                  ....
      ;  LODSD EAX... ESI+=4                 ....
        
   ; STOSB ES:EDI <- AL   EDI ++ if df = 0 ; df = 1 EDI -- 
    ;    W           AX      ...             ....
     ;   D           EAX     ...             ....
    
    ;MOVSB ES:EDI <- DS:ESI ; EDI++ ESI ++
     ;   w
      ;  d
      
    ;SCASB CMP AL, ES:EDI   EDI ++/--
      ;  W     AX
     ;   D     EAX
        
    ;CMPSB CMP DS:ESI, ES:EDI ;  ESI++/-- EDI++/--
    ;    W
   ;     D
        
  ;  pref instS

 ;   pref <- REP == REPE(Z)
    
    ;REPNE
    
    CLD
    mov ESI, s
    mov ECX, l
    mov EBX,0
    .r:
        LODSD
        LODSD
        shr EAX, 16
        mov AH, 0
        div byte [opt]; AH = AX%8
        cmp AH, 0
        jnz .c
            inc EBX
        .c:
        loop .r
            
    mov EAX, EBX
    
        
    .t:
        mov EDX, 0
        div dword [zece]
        add [sum], EDX
        cmp EAX, 0
        je .f
        
     
     
     
    .f:
    
    push dword 0
    call [exit]