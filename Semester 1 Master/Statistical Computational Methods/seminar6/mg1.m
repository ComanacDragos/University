clear all

t = cputime;

lamA = 5/60;
lamM1 = 1/2; # texts
lamM2 = 1/7; # attachments
p = 0.4;
N = 1e5; #input('size of MC study = ');

arrival = zeros(1, N);
start = zeros(1, N);
finish = zeros(1, N);

T=0;
A=0;


for j = 1:N;
  T = T-1/lamA * log(rand);
  S = -1/lamM1 * log(rand) - (rand<p) * 1/lamM2 * log(rand);
  arrival(j) = T;
  start(j) = max(A, T);
  finish(j) = start(j) + S;
  A = finish(j);
  
endfor
el_time = cputime-t;

fprintf('a) expected response time E(R) is %3.5f sec. \n', mean(finish-arrival))
fprintf('b) expected waiting time E(W) is %3.5f sec. \n', mean(start-arrival))

fprintf('CPU time = %f seconds \n', el_time)
