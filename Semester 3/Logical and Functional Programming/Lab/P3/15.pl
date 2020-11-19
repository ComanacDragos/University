/*
 * 15. For a given n, positive, determine all decomposition of n as a sum of consecutive natural numbers.

candidate(N)= 1. N
              2. candidate(N-1), N>1


decompositions_aux(N)= decompositions_rec(N, [e], e), e = candidate(N)

decompositions_rec(N, col1,...,coln, colSum) ={
                                 col1,...coln, colSum = N,
                                 decompositions_rec(N, e U
                                 col1,...,coln, e + colSum,
                                 (e=candidate(N)) = col1-1, e + colSum <=
                                 N,
                                 false, otherwise
                                 }
decompositions(N) = U decompositions_aux(N)

*/

%candidate(N: integer, Res:integer)
%(i,o) - non-deterministic
candidate(N, N).
candidate(N, Res):-N>1,
                   N1 is N-1,
                   candidate(N1, Res).

%decompositions_rec(N: integer, Res:list, Col: list, ColSum: integer)
%(i,o,i,i) - non-deterministic

decompositions_rec(N, [H1, H2|Col], [H1, H2|Col], N):-!.
decompositions_rec(N, Res, [H|Col], ColSum):-candidate(N, E),
                                             E is H-1,
                                             ColSum1 is E + ColSum,
                                             ColSum1 =< N,
                                             decompositions_rec(N, Res, [E| [H|Col]], ColSum1).

%decompositions_aux(N:integer, Res:list)
%(i,o) - non-deterministic
decompositions_aux(N, Res):-candidate(N, E),
                        decompositions_rec(N, Res, [E], E).

%decompositions(N:integer, Res:list)
%(i,o)
decompositions(N, Res):-findall(X, decompositions_aux(N, X), Res).