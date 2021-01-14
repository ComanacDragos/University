candidat([H|_], H).
candidat([_,H|T], R):-candidat([H|T],R).

bkt(_, S, Col, S, Col):-!.
bkt(L, S, [H||T], Scol, R):-candidat(L, C),
                            C < H,
                            S1 is Scol + C,
                            S1 =<S,
                            bkt(L, S,[C,H|T], S1, R).


wrapper(L,S,R):-candidat(L,C),
                bkt(L,S,[C], C, R).

