/*4.
a. Write a predicate to determine the difference of two sets.
b. Write a predicate to add value 1 after every even element from a list

find(el, l1,...,ln) = {
                        False, n = 0,
                        True, l1 = el
                        find(el, l2...,ln), altfel
                      }

difference(L1,...,Lm, l1,...ln)={
                              [], m = 0
                              L1 U difference(L2,...,Lm, l1...,ln),find(L1, l1,...,ln) = false
                              difference(L2,...,Lm, l1...,ln),find(L1,l1,...,ln) = true


addOnes(l1,...,ln) =
                    [], n = 0,
                    l1 U 1 U addOnes(l2,...,ln), l1%2 == 0,
                    l1 U addOnes(l2, ...,ln), altfel

 */

find(E, [E|_]):- !.
find(E, [_|T]):- find(E, T).

difference([], _, []):-!.
difference([H|T], L, Res):-find(H, L),
                           difference(T, L, Res), !.
difference([H|T], L, [H|Res]):-difference(T, L, Res).


addOnes([], []):-!.
addOnes([H|T], [H, 1 | Res]) :-
                                mod(H,2) =:= 0,
                                addOnes(T, Res), !.
addOnes([H|T], [H|Res]):-
                         addOnes(T, Res).
