clear all
pkg load statistics

n = input('n (in N) = ');
p = input('p in 0,1 = ');

%Y = ceil(log(1-rand(n,1))/log(1-p)-1);
%X = sum(Y)

err = input('error = ');
alpha = input('alpha = '); # level of significance

N = ceil(0.25*(norminv(alpha/2,0,1)/err)^2);

fprintf('Nr of sim N=%d\n\n', N);

X = zeros(1,N);
for i=1:N
  Y = ceil(log(1-rand(n,1))/log(1-p)-1);
  X(i) = sum(Y);
endfor


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