clear all;
pkg load statistics

err = 5e-3 #input('error = ');
alpha = 0.01 #input('alpha = '); # level of significance

N = ceil(0.25*(norminv(alpha/2,0,1)/err)^2);

fprintf('Nr of sim N=%d\n\n', N)

N_pi = 0;

for j=1:N
  X = unifrnd(-1,1);
  Y = unifrnd(-1,1);
  if X^2+Y^2<=1;
    N_pi = N_pi + 1;
  endif
endfor

aprox = 4*N_pi / N;

fprintf('pi = %1.10f\n', pi)
fprintf('aprox_pi = %1.10f\n', aprox)
fprintf('error = %e\n\n', abs(aprox-pi))

