f([],_,0).
f([H|T], V, P):-f(T,V,P1),P=P1*H.
f([_|T],V,P):-f(T,V,P).