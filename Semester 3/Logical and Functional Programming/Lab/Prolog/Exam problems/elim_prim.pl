prim(Nr, D):-Nr>=2,D*D>Nr,!.
prim(Nr, D):-Nr>2,
             Nr mod D =\=0,
             D1 is D+1,
             prim(Nr, D1).

elim([],_,[]).
elim([H|T], N, R):-N>0,
                   prim(H, 2),!,
                   N1 is N-1,
                   elim(T, N1, R).
elim([H|T], N, [H|R]):-elim(T, N, R).
