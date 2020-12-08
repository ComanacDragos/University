pkg load statistics

p = 0.5;
N = 10;

X = ones(1, N);
for i=1:N
  while rand() >= p
    X(i) += 1; 
  endwhile
endfor

X


