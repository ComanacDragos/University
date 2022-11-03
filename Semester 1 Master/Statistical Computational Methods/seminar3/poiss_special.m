clear all;
pkg load statistics

L = input("lambda (> 0) = ");

%U = rand;
%X = 0;
%while U >= exp(-L)
%  U = U * rand;
%  X = X + 1;
%end

err = 5e-3 #input('error = ');
alpha = 0.01 #input('alpha = '); # level of significance

N = ceil(0.25*(norminv(alpha/2,0,1)/err)^2);

fprintf('Nr of sim N=%d\n\n', N)

X = zeros(1, N);
for i=1:N 
  U = rand;
  while U >= exp(-L)
    U = U * rand;
    X(i) = X(i) + 1;
  end
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