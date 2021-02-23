candidate([H|_],H).
candidate([_|T], R):-candidate(T,R).


subsets(_,Col, SCol, Nrodd, Col):-SCol mod 2 =:=1,
                                  Nrodd mod 2 =:=1.
subsets(L,[H|T], Scol, Nrodd, R):-candidate(L,C),
                                  C<H,
                                  C mod 2 =:= 1,!,
                                  Scol1 is Scol + C,
                                  Nrodd1 is Nrodd + 1,
                                  subsets(L,[C,H|T], Scol1, Nrodd1, R).

subsets(L, [H|T], Scol, Nrodd, R):-candidate(L,C),
                                   C<H,
                                   Scol1 is Scol+C,
                                   subsets(L, [C,H|T], Scol1, Nrodd, R).

aux(L, R):-   candidate(L,C),
              Nrodd is C mod 2,
              subsets(L,[C], C, Nrodd,R).

main(L,R):-findall(X, aux(L,X),R).
