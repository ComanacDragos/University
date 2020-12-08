pkg load statistics

p1 = 0.5;
p2 = 0.3;
N = 1000;

X = ones(1, N);
for i=1:N
  while rand() >= p1 || rand() >= p2
    X(i) += 1; 
  endwhile
endfor

sum(X)/N

