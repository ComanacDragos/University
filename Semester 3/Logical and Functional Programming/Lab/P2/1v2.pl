/*
 1.
a. Sort a list with removing the double values. E.g.: [4 2 6 2 3 4] --> [2 3 4 6]
b. For a heterogeneous list, formed from integer numbers and list of numbers, write a predicate to sort every
sublist with removing the doubles.
Eg.: [1, 2, [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] =>
[1, 2, [1, 4], 3, 6, [1, 3, 7, 9, 10], 5, [1], 7].


insert(e, tree(root, left, right))={
                                   tree(e, nil, nil), tree(root, left,
                                   rigt) = nil
                                   tree(root, insert(e, left), right),
                                   e<=r
                                   tree(root, left, tree(e, right), else
                                   }
list2tree(l1,...,ln)={
                      nil, n=0,
                      insert(l1, list2tree(l2,...,ln)), else }


concatenate(l1,...,ln, j1,...,jm)={
                                  j1,...,jm, n=0
                                  l1 U concat(l2,...,ln, j1,...,jm)
                                  }

inorder(tree(root, left, right))={
                                 [], tree is nil
                                 inorder(left) U root U
                                 inorder(right), else
                                 }

treeSort(l1,...,ln)=inorder(list2tree(l1,...,ln))

inList(e, l1,...,ln)={
                      false, n=0
                      true, e=l1,
                      inList(e, l2,...,ln)
                      }

removeDuplicates(l1,...,ln)={
                           [], n=0,
                           removeDuplicates(l2,...,ln), inList(l1,
                           l2,...ln) = true
                           l1 U removeDuplicates(l2,...ln), else
                           }

removeSort(l1,...,ln)=removeDuplicates(treeSort(l1,...,ln))

removeSortSublists(l1,...,ln)={
                               [], n=0
                               removeSort(l1) U
                               removeSortSublists(l2,...,ln), l1 is a
                               list
                               l1 U removeSortSublists(l2,...,ln), else
                               }

*/

%tree(integer, tree, tree), nil

% insert(E: element, tree(Root: element, Left: tree, Right: tree), Res:
% tree) (i,i,o)
insert(E, nil, tree(E, nil, nil)):-!.
insert(E, tree(Root, Left, Right), tree(Root, Res, Right)):-E=<Root,!,
                                                            insert(E, Left, Res).
insert(E, tree(Root, Left, Right), tree(Root, Left, Res)):-insert(E, Right, Res).

% list2tree(L:list, Res: tree)
% (i,o)
list2tree([], nil).
list2tree([H|T], Res):-list2tree(T, Res1),
                       insert(H, Res1, Res).

%concatenate(L: list, J:list, Res:list)
%(i,i,o)
concatenate([], J, J).
concatenate([H|T], J, [H|Res]):-concatenate(T, J, Res).

%inorder(Tree: tree, Res: list)
inorder(nil, []).
inorder(tree(Root, Left, Right), Res):-inorder(Left, ResL),
                                       inorder(Right, ResR),
                                       concatenate(ResL, [Root], Res1),
                                       concatenate(Res1, ResR, Res).

%treeSort(L:list, Res:list)
%(i,o)
treeSort(L, Res):-list2tree(L, Res1),
                  inorder(Res1, Res).

%inList(E:element, L:list)
%(i,i)
inList(E, [E|_]):-!.
inList(E, [_|T]):-inList(E, T).


%removeDuplicates(L:List, Res:List)
%(i,o)
removeDuplicates([], []).
removeDuplicates([H|T], Res):-inList(H, T),!,
                             removeDuplicates(T, Res).
removeDuplicates([H|T], [H|Res]):-removeDuplicates(T, Res).

%removeSort(L:List, Res:list)
%(i,o)
removeSort(L, Res):-treeSort(L, Res1),
                    removeDuplicates(Res1, Res).


%removeSortSublists(L:list, Res:list)
%(i,o)
removeSortSublists([], []).
removeSortSublists([[H|T1]|T2], Res):-!,
                                      removeSort([H|T1], Res1),
                                      removeSortSublists(T2, Res2),
                                      Res = [Res1| Res2].
removeSortSublists([H|T], [H|Res]):-removeSortSublists(T, Res).
