/*11.
 a. Write a predicate to substitute an element from a list with another
 element in the list.
 b. Write a predicate to create the sublist (lm, �, ln) from the list
 (l1,�, lk).

substitute(elem, newElem, l1,...ln)= {
                                    [], n=0,
                                    newElem U substitute(elem, newElem, l2,...,ln), l1 == elem,
				    l1 U substitute(elem, newElem, l2,...ln), otherwise
}

sublist(M, N, l1,...,lk)= {
				[], k = 0
				[l1], N = 1 and M = 1
				l1 U sublist(1, N-1, l2...lk), M = 1
				sublist(M-1, N-1, l2,...lk), altfel
   }
*/

% substitute(Elem: element, NewElem: elemen, L: list, Result:list)
% (i, i, i, o)
substitute(_, _, [], []):-!.
substitute(Elem, NewElem, [Elem|T], [NewElem|Result]):-substitute(Elem, NewElem, T, Result), !.
substitute(Elem, NewElem, [H|T], [H|Result]):-substitute(Elem, NewElem, T, Result).

%sublist(M: integer, N: integer, L: list, Result: list)
%(i, i, i, o)
sublist(_, _, [], []):-!.
sublist(1, 1, [H|_], [H]):-!.
sublist(1, N, [H|T], [H|Result]):-N1 is N-1,
                                  sublist(1, N1, T, Result), !.
sublist(M, N, [_|T], Result):-M1 is M-1,
                              N1 is N-1,
                              sublist(M1, N1, T, Result).
