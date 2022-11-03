pkg load statistics
clear all

# generate GEO with DITM

p = input('p in 0,1 = ');

#X = ceil(log(1-rand)/log(1-p)-1)

err = input('error = ');
alpha = input('alpha = '); # level of significance

N = ceil(0.25*(norminv(alpha/2,0,1)/err)^2);

fprintf('Nr of sim N=%d\n\n', N);

X = zeros(1, N);
for i=1:N
  X(i) = ceil(log(1-rand)/log(1-p)-1); # geo variables
endfor

fprintf('sim prob. P(X=2) = %1.5f\n', mean(X==2))
fprintf('true prob. P(X=2) = %1.5f\n', geopdf(2,p))
fprintf('error = %e\n\n', abs(geopdf(2,p)- mean(X==2)))

fprintf('sim prob. P(X<=2) = %1.5f\n', mean(X<=2))
fprintf('true prob. P(X<=2) = %1.5f\n', geocdf(2,p))
fprintf('error = %e\n\n', abs(geocdf(2,p)- mean(X<=2)))


fprintf('sim prob. P(X<2) = %1.5f\n', mean(X<2))
fprintf('true prob. P(X<2) = %1.5f\n', geocdf(1,p)) % because strictly less
fprintf('error = %e\n\n', abs(geocdf(1,p)- mean(X<2)))

fprintf('sim mean E(X) = %5.5f\n', mean(X))
fprintf('true mean E(X) = %5.5f\n', (1-p)/p) 
fprintf('error = %e\n\n', abs((1-p)/p - mean(X)))