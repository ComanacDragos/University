clear all;
pkg load statistics

p = input("p in (0,1) = ");
n = input('nr of successes = ');
N = input('nr of simulations = ');


X = zeros(1, N);
for i=1:N
   Y = zeros(1, n);
   for j =1:n
    Y(j) = 0;
    while rand >= p
      Y(j) = Y(j) + 1;
    endwhile
   endfor
   X(i) = sum(Y);
endfor

% OR
% U = rand(n, N)
% X = sum(U<p)

fprintf('sim prob. P(X=2) = %1.5f\n', mean(X==2))
fprintf('true prob. P(X=2) = %1.5f\n', nbinpdf(2,n,p))
fprintf('error = %e\n\n', abs(nbinpdf(2,n,p)- mean(X==2)))

fprintf('sim prob. P(X<=2) = %1.5f\n', mean(X<=2))
fprintf('true prob. P(X<=2) = %1.5f\n', nbincdf(2,n,p))
fprintf('error = %e\n\n', abs(nbincdf(2,n,p)- mean(X<=2)))


fprintf('sim prob. P(X<2) = %1.5f\n', mean(X<2))
fprintf('true prob. P(X<2) = %1.5f\n', nbincdf(1,n,p)) % because strictly less
fprintf('error = %e\n\n', abs(nbincdf(1,n,p)- mean(X<2)))

fprintf('sim mean E(X) = %5.5f\n', mean(X))
fprintf('true mean E(X) = %5.5f\n', n*(1-p)/p) 
fprintf('error = %e\n\n', abs(n*(1-p)/p - mean(X)))