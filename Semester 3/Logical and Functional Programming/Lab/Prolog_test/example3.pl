mama(a,b).
mama(e,b).

tata(c,d).
tata(a,d).


parinte(X,Y):-tata(X,Y).
parinte(X,Y):-mama(X,Y).

frate(X,Y):- parinte(X,Z),
              parinte(Y,Z),
              X\=Y.

