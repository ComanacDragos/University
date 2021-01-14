lungime([],0):-!.
lungime([_|T], R):-lungime(T, R1),
                   R is R1+1.

elim([],_, []):-!.
elim(L,0,L):-!.
elim([H|T], N, R):-lungime(H,K),
                   K mod 2 =:=0,!,
                   N1 is N-1,
                   elim(T,N1,R).
elim([H|T], N, [H|R]):-elim(T,N,R).

