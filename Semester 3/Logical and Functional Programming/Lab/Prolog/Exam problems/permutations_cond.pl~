candidat(N,R):-R is N-1.
candidat(N,R):-N>1,
               N1 is N-1,
               candidat(N1,R).


apare(H, [H|_]):-!.
apare(El, [_|T]):-apare(El,T).


permutari(N,N,Col,Col):-!.
permutari(N,Lcol,[H|T],R):-Lcol<N,
                           candidat(N,C),
                           C1 is C+N,
                           abs(C1-H)=<2,
                           \+apare(C1,[H|T]),
                           LCol1 is Lcol+1,
                           permutari(N,LCol1, [C1,H|T],R).

wrapper(N,R):-candidat(N,C),
              C1 is C+N,
              permutari(N,1,[C1],R).

main(N,R):-findall(X,wrapper(N,X),R).
