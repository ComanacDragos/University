clear all
pkg load statistics

L = input('lambda >0 = ');
a = input('a positive integer = ');

err = 5e-3 #input('error = ');
alpha = 0.01 #input('alpha = '); # level of significance

N = ceil(0.25*(norminv(alpha/2,0,1)/err)^2);

fprintf('Nr of sim N=%d\n\n', N)

X = zeros(1, N);

for i=1:N
  X(i) = sum(-L*log(rand(a,1)));
endfor

fprintf('sim prob. P(X<=2) = %1.5f\n', mean(X<=2))
fprintf('true prob. P(X<=2) = %1.5f\n', gamcdf(2, a, L))
fprintf('error = %e\n\n', abs(gamcdf(2, a, L)- mean(X<=2)))


fprintf('sim prob. P(X<2) = %1.5f\n', mean(X<2))
fprintf('true prob. P(X<2) = %1.5f\n', gamcdf(2, a, L)) % because strictly less
fprintf('error = %e\n\n', abs(gamcdf(2, a, L)- mean(X<2)))

fprintf('sim mean E(X) = %5.5f\n', mean(X))
fprintf('true mean E(X) = %5.5f\n', a*L) 
fprintf('error = %e\n\n', abs(a*L- mean(X)))
