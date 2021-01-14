power(_,0,1):-!.
power(X,1,X):-!.
power(X,N,R):- N mod 2 =\= 0,!,
               N1 is N div 2,
               power(X, N1, R1),
               R is R1*R1*X.
power(X,N,R):- N1 is N div 2,
               power(X, N1, R1),
               R is R1*R1.

power2(_,0,1):-!.
power2(X,N,R):-N1 is N-1,
               power2(X, N1,R1),
               R is X*R1.
