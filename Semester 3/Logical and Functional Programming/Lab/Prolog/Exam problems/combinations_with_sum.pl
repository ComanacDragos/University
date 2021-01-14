candidat([H|_], H).
candidat([_|T], R):-candidat(T, R).

combinari(_, S, K, Col, S, K, Col):-!.
combinari(L, S, K, [H|T], SCol, KCol, R):-KCol<K,
                                          SCol<S,
                                          candidat(L, C),
                                          C<H,
                                          SCol1 is SCol+C,
                                          KCol1 is KCol+1,
                                          combinari(L, S, K, [C,H|T], SCol1, KCol1, R).

wrapper(L,S,K,R):-candidat(L,C),
                  C =<S,
                  combinari(L,S,K, [C], C, 1, R).

main(L,S,K,R):-findall(X, wrapper(L,S,K,X),R).
