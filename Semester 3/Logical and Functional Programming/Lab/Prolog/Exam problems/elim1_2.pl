apare([H|_], H):-!.
apare([_|T], El):-apare(T,El).

elim1([],[]):-!.
elim1([H|T], R):-apare(T,H),!,
                 elim1(T,R).
elim1([H|T], [H|R]):-elim1(T,R).

elim2([], Col, Col).
elim2([H|T], Col,R):-apare(Col, H),!,
                     elim2(T, Col, R).
elim2([H|T], Col, R):-elim2(T,[H|Col],R).

main(L, R):-elim2(L, [],R).
