/*
 Write a program to generate the list of all subsets of sum S with the elements of a list (S - given).
Eg: [1,2,3,4,5,6,10] si S=10 => [[1,2,3,4], [1,4,5], [2,3,5], [4,6], [10]] (not necessary in this order)

candidate(l1,...,ln)={
                     1. l1, n>0
                     2. candidate(l2,...,ln)
}

generareSubmultimi(l1,...,ln, S)= generareSubmultimiAux(l1,...,ln, S,
[e], e), (e = candidate(l1,...,ln)) <= S

generareSubmultimiAux(l1,...,ln, S, col1,...,coln, sumCol)=={
                                       col1,...,col, S = sumCol,
                                       generareSubmultimiAux(l1,...,ln,
                                       S, e U col1,...,coln, e +
                                       sumCol), (e =
                                       candidate(l1,...,ln)) < col1 and
                                       sumCol + e <= S
                                       }
*/

%candidate(L: list, E: integer)
%(i, o)
candidate([E|_], E).
candidate([_|T], E):- candidate(T, E).

% generareSubmultimiAux(L:list, S:integer, Res:list, Col: list, SumCol:
% integer) (i,i,o,i,i)

generareSubmultimiAux(_, S, Col, Col, S):-!.
generareSubmultimiAux(L, S, Res, [H|Col], SumCol):-
                                                 candidate(L, E),
                                                 E < H,
                                                 S1 is SumCol + E,
                                                 S1 =< S,
                                                 generareSubmultimiAux(L, S, Res, [E|[H|Col]], S1).

generareSubmultimi(L, S, Res):-candidate(L, E),
                               E =< S,
                               generareSubmultimiAux(L, S, Res, [E], E).

%generare(L, S, Res):- findall(X, generareSubmultimi(L, S, X), Res).
generareAux(L, S, Res, R):-generareSubmultimi(L, S, Res1),
                        Res = [Res1 | Res],
                        R = Res.

generare(L, S, Res):-generareAux(L, S, [], Res).
