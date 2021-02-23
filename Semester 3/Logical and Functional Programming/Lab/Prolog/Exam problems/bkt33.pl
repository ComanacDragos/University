candidat(A,_,A).
candidat(A,B,R):-A<B,
                 A1 is A+1,
                 candidat(A1,B,R).

sub(_,_,P,I,Col,Col):-P>0,
                      P mod 2 =:= 0,
                      I mod 2 =:= 1.
sub(A,B,P,I,[H|T],R):-candidat(A,B,C),
                    C<H,
                    P1 is P + (C+1) mod 2,
                    I1 is I + C mod 2,
                    sub(A,B,P1, I1, [C,H|T],R).

wrapper(A,B,R):-candidat(A,B,C),
                P is (C+1) mod 2,
                I is C mod 2,
                sub(A,B,P,I,[C],R).

main(A,B,R):-findall(X,wrapper(A,B,X),R).




