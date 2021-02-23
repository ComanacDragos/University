candidat([H|_],H).
candidat([_|T], R):-candidat(T,R).

apare(H,[H|_]):-!.
apare(El,[_|T]):-apare(El,T).


lungime([],0):-!.
lungime([_|T],R):-lungime(T,R1),
                  R is R1+1.


permutari(_,N,Col,N,Col):-!.
permutari(L,N,[H|T],LCol,R):-LCol<N,
                             candidat(L,C),
                             abs(C-H) =< 3,
                             \+ apare(C,[H|T]),
                             LCol1 is LCol+1,
                             permutari(L,N,[C,H|T],LCol1,R).

wrapper(L,N,R):-candidat(L,C),
                permutari(L,N,[C],1,R).

main(L,R):-lungime(L,N),
           findall(X, wrapper(L,N,X),R).