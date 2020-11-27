pkg load statistics

p = 0.6;
N = 1000;

X = zeros(1, N);
for i=1:N
  while rand() >= p
    X(i) += 1; 
  endwhile
endfor


U_X = unique(X);
N_X = hist(X, length(U_X));
F_X = N_X/N;


plot(1:40, geopdf(1:40, p), 'g*');
hold on; 
plot(U_X, F_X, 'b*');
