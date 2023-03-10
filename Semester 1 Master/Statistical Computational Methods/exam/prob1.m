clear all;
pkg load statistics

p = 0.1#input("p in (0,1) = ");
N = input('nr of simulations = ');


%X=0;
%while rand >= p
%   X=X+1;
%endwhile


X = zeros(1, N);
for i=1:N
   while rand >= p 
    X(i) = X(i) + 1;
   endwhile
endfor

% OR
% U = rand(n, N)
% X = sum(U<p)

#fprintf('sim prob. P(X=2) = %1.5f\n', mean(X==2))
#fprintf('true prob. P(X=2) = %1.5f\n', geopdf(2,p))
#fprintf('error = %e\n\n', abs(geopdf(2,p)- mean(X==2)))

#fprintf('sim prob. P(X<=2) = %1.5f\n', mean(X<=2))
#fprintf('true prob. P(X<=2) = %1.5f\n', geocdf(2,p))
#fprintf('error = %e\n\n', abs(geocdf(2,p)- mean(X<=2)))


fprintf('a')
fprintf('sim prob. P(X>=7) = 1 - P(X<7) = %1.5f\n', 1-mean(X<7))
fprintf('true prob. P(X>=7) = 1 - P(X<7) = %1.5f\n', geocdf(6,p)) % because strictly less
fprintf('error = %e\n\n', abs(geocdf(1,p)- mean(X<2)))


fprintf('b')
fprintf('sim mean E(X) = %5.5f\n', mean(X))
fprintf('true mean E(X) = %5.5f\n', (1-p)/p) 
fprintf('error = %e\n\n', abs((1-p)/p - mean(X)))