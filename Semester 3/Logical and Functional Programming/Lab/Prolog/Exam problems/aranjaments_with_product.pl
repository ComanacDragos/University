candidat([H|_], H).
candidat([_,H2|T], R):-candidat([H2|T],R).

bkt(_, K, P, Col, K, P, Col):-!.
bkt(L, K, P, Col, LCol, PCol, R):- LCol < K,
                                   PCol < P,
                                   candidat(L, C),
                                   \+ apare(Col, C),
                                   LCol1 is LCol + 1,
                                   PCol1 is PCol*C,
                                   bkt(L, K, P, [C|Col], LCol1, PCol1, R).

main(L,K,P,R):-findall(X, bkt(L, K, P, [],0,1,X),R).

apare([H|_], H):-!.
apare([_|T], El):-apare(T,El).
