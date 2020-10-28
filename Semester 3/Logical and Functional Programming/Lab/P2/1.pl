/*
 1.
a. Sort a list with removing the double values. E.g.: [4 2 6 2 3 4] --> [2 3 4 6]
b. For a heterogeneous list, formed from integer numbers and list of numbers, write a predicate to sort every
sublist with removing the doubles.
Eg.: [1, 2, [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] =>
[1, 2, [1, 4], 3, 6, [1, 3, 7, 9, 10], 5, [1], 7].

inOrder(l1,...,ln)={
                    true, n = 0 or n = 1,
                    inOrder(l2,...,ln), l1 < l2,
                    false, altfel

swapOne(l1,...,ln)={
                    [], n = 0
                    [l1], n = 1,
                    l2, l1,...,ln, l1>l2,
                    swapOne(l2,...,ln), l1 = l2,
                    l1 + swapOne(l2,...,ln), else
                    }

bubbleSort(l1,...,ln)={
                    [], n=0
                    [l1], n=1,
                    l1,...,ln, inOrder(l1,...,ln),
                    bubbleSort(swapOne(l1,...,ln)), else
                    }

bubbleSortSublists(l1,...,ln)={
                              [], n=0,
                              bubbleSort(l1) +
                              bubbleSortSublists(l2,...,ln), l1 is a
                              list,
                              l1 + bubbleSortSublists(l2,...,ln), else
                              }

*/
%inOrder(L:list)
%(i)
inOrder([]).
inOrder([_]):-!.
inOrder([A,B|T]):-A<B,
                  inOrder([B|T]).

%swapOne(L:list, Res:list)
%(i,o)
swapOne([], []).
swapOne([H], [H]):-!.
swapOne([A,B|T], [B,A|T]):-A>B, !.
swapOne([A,A|T], [A|Res]):-swapOne(T, Res),!.
swapOne([A|T], [A|Res]):-swapOne(T, Res).

%bubbleSort(L:list, Res:list)
%(i,o)
bubbleSort([], []).
bubbleSort([H], [H]):-!.
bubbleSort([H|T], [H|T]):-inOrder([H|T]), !.
bubbleSort([H|T], Res):-swapOne([H|T], Res1),
                        bubbleSort(Res1, Res).


%bubbleSortSublists(L:list, Res:list)
%(i,o)
bubbleSortSublists([], []).
bubbleSortSublists([[H|T1]|T2], Res):-!,
                                      bubbleSort([H|T1], Res1),
                                      bubbleSortSublists(T2, Res2),
                                      Res = [Res1|Res2].
bubbleSortSublists([H|T], [H|Res]):-bubbleSortSublists(T, Res).


