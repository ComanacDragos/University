clear all;
pkg load statistics

err = 5e-3 #input('error = ');
alpha = 0.01 #input('alpha = '); # level of significance

N = ceil(0.25*(norminv(alpha/2,0,1)/err)^2);

fprintf('Nr of sim N=%d\n\n', N)

k = 4;#input('number of previous days considered')
in_last = [10,5,7,6];#input('number of errors in the last k days')

t_max = 10;#input('max time after the new software is withdrawn');

Ttotal = zeros(1,N); # total time to find the errors
NTotalerr = zeros(1,N); # total number of errors that are detected

for i=1:N
  # T is time from now on in days, X is the nr of errors on day T
  # nerr is the number of errors detected so far
  printf("sim %d/%d\n", i, N);
  T = 0;
  X = in_last(k);
  nerr = sum(in_last);
  last = in_last;
  while X>0;
    lambda = min(last); # par for var X
     # simulate the number of err in day T
     # possion lambda special method
    U = rand;
    X = 0;
    while U >= exp(-lambda);
      U = U * rand;
      X = X + 1;
    endwhile
    T = T+1;
    nerr = nerr + X;
    last = [last(2:k), X];
  endwhile
  Ttotal(i) = T-1; # the day all errors were found
  NTotalerr(i) = nerr; # total nr of errors found
endfor

fprintf('\n')

fprintf('a) The time it will take to find all errors is %3.3f days\n', mean(Ttotal))
fprintf('b) Total number of errors in new release is %5.3f \n', mean(NTotalerr))
fprintf('c) Prob. that some errors will be undetected after %d days\n', t_max)
fprintf('after which the software will be withdrawn is %1.3f \n', mean(Ttotal>t_max))


