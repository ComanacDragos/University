clear all;
pkg load statistics

p = input("p in (0,1) = ");
n = input('nr of trials = ');
N = input('nr of simulations = ');


%U = rand(n, 1);
%X = sum(U<p)

X = zeros(1, N);
for i=1:N
   U = rand(n, 1);
   X(i) = sum(U < p);
endfor

% OR
% U = rand(n, N)
% X = sum(U<p)

fprintf('sim prob. P(X=2) = %1.5f\n', mean(X==2))
fprintf('true prob. P(X=2) = %1.5f\n', binopdf(2,n,p))
fprintf('error = %e\n\n', abs(binopdf(2,n,p)- mean(X==2)))

fprintf('sim prob. P(X<=2) = %1.5f\n', mean(X<=2))
fprintf('true prob. P(X<=2) = %1.5f\n', binocdf(2,n,p))
fprintf('error = %e\n\n', abs(binocdf(2,n,p)- mean(X<=2)))


fprintf('sim prob. P(X<2) = %1.5f\n', mean(X<2))
fprintf('true prob. P(X<2) = %1.5f\n', binocdf(1,n,p)) % because strictly less
fprintf('error = %e\n\n', abs(binocdf(1,n,p)- mean(X<2)))

fprintf('sim mean E(X) = %5.5f\n', mean(X))
fprintf('true mean E(X) = %5.5f\n', n*p) 
fprintf('error = %e\n\n', abs(n*p- mean(X)))