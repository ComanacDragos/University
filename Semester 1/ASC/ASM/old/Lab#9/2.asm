bits 32
global start

extern exit, scanf, fprintf, fopen
import fopen msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll
import exit msvcrt.dll

segment data use32 class=data
    file_name db "file.txt", 0
    f_str db "%s", 0
    stop db "$", 0
    mode dd "w", 0
    buffer resb 100
    d_f resd 1
    f_d db "%s", 10, 0
    
segment code use32 class=code
;  cititm mai multe siruri pana citim $
; le scriem in fisier daca au cel putin o litera mica
    start:
    push mode
    push file_name
    call [fopen]
    add ESP, 4*2
    
    
    
    
    cmp EAX, 0
    jz end
    
    mov [d_f], EAX
    
    
    loop1:
        
        push buffer
        push f_str
        call [scanf]
        add ESP, 4*2
        

        mov ESI, buffer
        loop2:
            lodsb
            cmp AL, 0
            jz loop_end
            
            cmp AL, 'a'
            jb loop2_end
            
            cmp AL, 'z'
            ja loop2_end

            push buffer
            push f_d
            push dword [d_f]
            call [fprintf]
            add ESP, 4*3
            
            jmp loop_end
            
        loop2_end:
            jmp loop2
            
        loop_end:
        mov DL, [stop]
        cmp [buffer], DL
        jne loop1
        
    
    end:
    push dword 0
    call [exit]