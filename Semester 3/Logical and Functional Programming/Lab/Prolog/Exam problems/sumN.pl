sum1(0,0):-!.
sum1(N, R):-N1 is N-1,
            sum1(N1, R1),
            R is N + R1.

sum2(N,R):-R is N*(N+1)/2.
