/*1.
a. Write a predicate to determine the lowest common multiple of a list formed from integer numbers.
b. Write a predicate to add a value v after 1-st, 2-nd, 4-th, 8-th, � element in a list.


cmmdc(e1, e2)= e1, e1=e2
               cmmdc(e1-e2, e2), e1>e2
               cmmdc(e1, e2-e1), altfel

cmmdc_multiplu(l1,l2,...,ln) = l1, n = 1,
                               cmmdc(l1, l2), n=2,
                               cmmdc(l1, cmmdc_multiplu(l2,...,ln),altfel

product(l1,...,ln) = 1, n = 0
                     l1 * product(l2,...,ln), altfe


cmmmc(l1,...,ln) = product(l1,..., ln) / cmmdc_multiplu(l1,...,ln)
*/

cmmdc(E, E, E):-!.
cmmdc(A, B, Res):-A>B,
                    A1 is A-B,
                    cmmdc(A1, B, Res), !.
cmmdc(A, B, Res):-B1 is B-A,
                  cmmdc(A, B1, Res).

cmmdc_multiplu([H|[]], H):-!.
cmmdc_multiplu([A, B | []], Res):-cmmdc(A, B, Res), !.
cmmdc_multiplu([H|T], Res):-cmmdc_multiplu(T, SubRes),
                            cmmdc(H, SubRes, Res).




product([], 1):-!.
product([H|T], Res):-product(T, SubRes),
                     Res is H * SubRes.


cmmmc(A, B, Res):- product([A,B], P),
                   cmmdc(A,B, C),
                   Res is P div C.

cmmmc_multiplu([H], H):-!.
cmmmc_multiplu([A, B], Res):- cmmmc(A, B, Res), !.
cmmmc_multiplu([H|T], Res):- cmmmc_multiplu(T, SubRes),
                             cmmmc(H, SubRes, Res).

/*
 *
 addValue_rec(v, i, p, l1,...,ln) = {
                                 [], n = 0
                                 l1 U v U addValue_rec(v, i+1,
                                 p*2,l2,...,ln), i = p
                                 l1 U addValue_rec(v, i + 1, p,
                                 l2,...,ln), altfel

addVal(v, l1,...,ln) = adauga_rec(v, 1, 1, l1,...,ln)
*/


addValue_rec(_, _, _, [], []):-!.
addValue_rec(V, I, P, [H|T], [H, V | Res]):-I=:=P,
                                   I1 is I+1,
                                   P1 is P*2,
                                   addValue_rec(V, I1, P1, T, Res),!.
addValue_rec(V, I, P, [H|T], [H|Res]):-I1 is I+1,
                                       addValue_rec(V, I1, P, T, Res).


addValue(V, L, Res):-addValue_rec(V, 1, 1, L, Res).
