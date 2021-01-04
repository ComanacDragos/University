candidat([H|_], H).
candidat([_, H|T], R):- candidat([H|T], R).

apare([H|_], H):-!.
apare([_|T], El):-apare(T, El).

aranjamente(N,_,S,N,Col,S,Col):-!.
aranjamente(N, L, S, LCol, Col, SCol, R):-LCol<N,
                                          SCol<S,
                                          candidat(L, C),
                                          \+ apare(Col, C),
                                          LCol1 is LCol +1,
                                          SCol1 is SCol + C,
                                          aranjamente(N, L, S, LCol1, [C|Col], SCol1, R).

main(N, L, S, R):-findall(X, aranjamente(N, L, S, 0, [], 0, X), R).
