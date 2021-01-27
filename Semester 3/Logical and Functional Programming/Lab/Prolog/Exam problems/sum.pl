sum(N, R):-R is 3*N*(N+1) div 2.

sum2(0,0):-!.
sum2(N,R):- N1 is N-1,
            sum2(N1,R1),
            R is 3*N + R1.
