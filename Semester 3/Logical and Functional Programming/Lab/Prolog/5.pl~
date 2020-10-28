/*
 * 5.
a. Substitute all occurrences of an element of a list with all the elements of another list.
Eg. subst([1,2,1,3,1,4],1,[10,11],X) produces X=[10,11,2,10,11,3,10,11,4].
b. For a heterogeneous list, formed from integer numbers and list of numbers, replace in every sublist all
occurrences of the first element from sublist it a new given list.
Eg.: [1, [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] si [11, 11] =>
[1, [11, 11, 1, 11, 11], 3, 6, [11, 11, 10, 1, 3, 9], 5, [11 11 11 11 11 11], 7]


concat(j1,...,jm, l1,...,ln)={
                              l1,...,ln, m=0
                              j1 + concat(j2,...,jm, l1,...,ln), altfel
                              }

substitute(l1,...,ln, el, j1,...,jm) ={
                                      [], n=0,
                                      concat(j1,...,jm, substitute(l2,
                                      ...ln, el, j1, ....,jm)),l1=el
                                      l1 + substitute(l2,...,ln, el,
                                      j1,...,jm), altfel
                                      }

substituteList(l1,..., ln, j1,...,jm)={
                                     [], n=0,
                                     substitute(l1, l1_1, j1,...,jm)
                                     + substituteList(l2,...,ln,
                                     j1,...,jm),if l1 is a list
                                     l1 +
                                     substituteList(l2,...,ln,j1,...,jm),
 altfel
 }

*/
%concat(J: list, L: list, Res:list)
%(i, i, o), (i, i, i)
concatenate([], L, L).
concatenate([H|T], L, [H|Res]):-concatenate(T, L, Res).

%substitute(L: list, El, J: List, Res: list)
%(i,i,i,o), (i,i,i,i)

substitute([], _, _, []):-!.
substitute([H|T], H, J, Res):-!,
                              substitute(T, H, J, Res1),
                              concatenate(J, Res1, Res).
substitute([H|T], El, J, [H|Res]):-substitute(T, El, J, Res).

%substituteList(L: list, J: list, Res:List)
%(i, i, o), (i, i,i)

substituteList([], _, []):-!.
substituteList([[H|T1]|T2], J, Res):-!,
                                     substitute([H|T1], H, J, Res1),
                                     substituteList(T2, J, Res2),
                                     Res = [Res1|Res2].
substituteList([H|T], J, [H|Res]):-substituteList(T, J, Res).






