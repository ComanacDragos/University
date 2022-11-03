clear all
pkg load statistics

L = input('lambda >0 = ');

err = 5e-3 #input('error = ');
alpha = 0.01 #input('alpha = '); # level of significance

N = ceil(0.25*(norminv(alpha/2,0,1)/err)^2);

fprintf('Nr of sim N=%d\n\n', N)

X = zeros(1, N);

for i=1:N
  X(i) = -1/L*log(rand);
endfor


fprintf('sim prob. P(X<=2) = %1.5f\n', mean(X<=2))
fprintf('true prob. P(X<=2) = %1.5f\n', expcdf(2,1/L))
fprintf('error = %e\n\n', abs(expcdf(2,1/L)- mean(X<=2)))


fprintf('sim prob. P(X<2) = %1.5f\n', mean(X<2))
fprintf('true prob. P(X<2) = %1.5f\n', expcdf(2,1/L)) % because strictly less
fprintf('error = %e\n\n', abs(expcdf(2,1/L)- mean(X<2)))

fprintf('sim mean E(X) = %5.5f\n', mean(X))
fprintf('true mean E(X) = %5.5f\n', 1/L) 
fprintf('error = %e\n\n', abs(1/L- mean(X)))
