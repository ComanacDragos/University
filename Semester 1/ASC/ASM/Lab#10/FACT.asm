%ifndef _FACTd_ASM_
%define _FACTd_ASM_

factorial:
        mov EAX, 1
        mov EBX, [ESP+4]
        mov ECX, [EBX]
        l:
            mul ECX
        loop l
        
        ret 



%endif