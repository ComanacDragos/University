max([H],H):-!.
max([H|T], R):-max(T,R1),
               aux(H,R1,R).
aux(H,R1,H):-H>R1,!.
aux(_,R1,R1).

sterge(_,[],[]):-!.
sterge(H,[H|T],R):-!,sterge(H,T,R).
sterge(El,[H|T],[H|R]):-sterge(El,T,R).

main([],[]).
main([[H|T1]|T2], R):-!,
                     max([H|T1], M),
                     sterge(M,[H|T1], R1),
                     main(T2,R2),
                     R=[R1|R2].
main([H|T], [H|R]):-main(T,R).
