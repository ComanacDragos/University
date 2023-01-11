clear all

tcpu = cputime;

alpha = 4;
lambda = 10/3;
t=15;

N = 1e5;#input('size of MC study = ');

arrival = 0:t:(N-1)*t;

start = zeros(1, N);

finish = zeros(1,N);

A = 0;

for j=1:N
  start(j) = max(A, arrival(j));
  S = -lambda * sum(log(rand(alpha, 1)));
  finish(j) = start(j) + S;
  A = finish(j);
  
endfor
el_time = cputime - tcpu;

fprintf('a) prob. that a patient has to wait P(W>0) is %3.5f \n', mean(start>arrival))
fprintf('b) expected waiting time E(W) is %3.5f min\n', mean(start-arrival))

fprintf('CPU time = %f seconds \n', el_time)
