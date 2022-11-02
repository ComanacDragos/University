clear all;
pkg load statistics

L = input("lambda (> 0) = ");
N = input('nr of simulations = ');

F = zeros(1, N);
X = zeros(1, N);
for j=1:N
   i=0;
   F(j) = exp(-L);
   U = rand;
   while (U >= F(j))
    F(j) = F(j) + exp(-L) * L^i/factorial(i);
    i = i+1;    
   end
   X(j) = i;
endfor

fprintf('sim prob. P(X=2) = %1.5f\n', mean(X==2))
fprintf('true prob. P(X=2) = %1.5f\n', poisspdf(2,L))
fprintf('error = %e\n\n', abs(poisspdf(2,L)- mean(X==2)))

fprintf('sim prob. P(X<=2) = %1.5f\n', mean(X<=2))
fprintf('true prob. P(X<=2) = %1.5f\n', poisscdf(2,L))
fprintf('error = %e\n\n', abs(poisscdf(2,L)- mean(X<=2)))


fprintf('sim prob. P(X<2) = %1.5f\n', mean(X<2))
fprintf('true prob. P(X<2) = %1.5f\n', poisscdf(1,L)) % because strictly less
fprintf('error = %e\n\n', abs(poisscdf(1,L)- mean(X<2)))

fprintf('sim mean E(X) = %5.5f\n', mean(X))
fprintf('true mean E(X) = %5.5f\n', L) 
fprintf('error = %e\n\n', abs(L- mean(X)))