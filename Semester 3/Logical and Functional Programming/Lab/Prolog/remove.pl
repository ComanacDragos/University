remove(_, [], []):-!.
remove(H, [H|T], Res):-remove(H, T, Res),!.
remove(V, [H|T], [H|Res]):-remove(V,T,Res).

/*
 *
 * remove(el, l1,...,ln)=
 *                   [], n=0
 *                   remove(el,l2,...,ln), el = l1,
 *                   l1 U remove(el, l2,...,ln), altfel
 *                   */
