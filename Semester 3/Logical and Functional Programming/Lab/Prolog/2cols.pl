cmmdc(A,A,A):-!.
cmmdc(A,B,R):-A>B,!,
              A1 is A-B,
              cmmdc(A1, B,R).
cmmdc(A,B,R):-B1 is B-A,
              cmmdc(A,B1,R).

cmmdcl([H], H):-!.
cmmdcl([H|T], R):-cmmdcl(T,R1),
                  cmmdc(H,R1, R).

medie([], S, L, R):- R is S / L.
medie([H|T], S,L,R):-S1 is S+H,
                     L1 is L +1,
                     medie(T,S1, L1,R).

candidate([H|_], H).
candidate([_|T], R):-candidate(T,R).

elim(_, [],[]):-!.
elim(El, [El|T], R):-elim(El, T,R),!.
elim(El, [H|T], [H|R]):-elim(El, T, R).


aux(_, S,D,R):-medie(S,0,0,M),
               cmmdcl(D,C),
               M=<C,
               R=[S,D].
/*
aux(L, [H|T], D,R):-candidate(L,C),
                    candidate([H|T], C),
                    candidate(D,C),
                    C<H,
                    aux(L, [C, H|T],D,R).
aux(L,S,[H|T], R):-candidate(L,C),
                   candidate([H|T], C),
                   candidate(S,C),
                   C<H,
                   aux(L, S, [C,H|T],R).

main(L,R):-candidate(L,C1),
           candidate(L,C2),
           C1 =\= C2,
           aux(L,[C1],[C2], R).
*/

aux(L, [H|T],D,R):-candidate(D,C),
               elim(C, D, D1),
               C<H,
               aux(L,[C,H|T],D1,R).

main(L,R):-candidate(L,C),
           elim(C,L,D),
           aux(L,[C], D,R).






