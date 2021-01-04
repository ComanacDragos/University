candidat(N, R):-R is N-1.
candidat(N, R):-N>1,
                N1 is N-1,
                candidat(N1, R).

apare(El, [El|_]):-!.
apare(El, [_|T]):-apare(El, T).

permutari_aux(N, N, Col, Col):-!.
permutari_aux(N, LCol, [H|T], R):-candidat(N, C1),
                                  C is C1+N,
                                  abs(H-C)=<2,
                                  \+ apare(C, [H|T]),
                                  LCol1 is LCol + 1,
                                  permutari_aux(N, LCol1, [C, H|T], R).

permutari(N, R):-candidat(N, C1),
                 C is C1+N,
                 permutari_aux(N, 1, [C], R).

main(N, R):-findall(X, permutari(N, X), R).
