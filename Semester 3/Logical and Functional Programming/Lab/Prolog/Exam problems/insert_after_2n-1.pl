adaug([],_,_,_,[]):-!.
adaug([H|T], E, I, I, [H, E| R]):-!,
                           I1 is I+1,
                           M1 is 2*I-1,
                           adaug(T, E, I1, M1, R).
adaug([H|T], E, I, M, [H|R]):-I1 is I+1,
                              adaug(T, E, I1, M, R).
