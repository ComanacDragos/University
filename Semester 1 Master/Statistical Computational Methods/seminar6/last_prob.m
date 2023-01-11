clear all

tcpu = cputime;

alpha = 4;
lambda = 10/3;
t=15;

Tmax = 600;#input(’maximum time (in minutes) = ’);
N = 1e5;#input('size of MC study = ');
Nmax = Tmax/15;

arrival = 0 : t : (Nmax - 1)*t;




expw = zeros(1, N); % expected waiting time for each simulationmaxw = zeros(1, N); % maximum waiting time for each simulationnr_p = zeros(1, N); % number of patients in the clinic at% the end of the day for each simulation
maxw = zeros(1, N); % maximum waiting time for each simulation
nr_p = zeros(1, N); % number of patients in the clinic at

for i = 1 : N
  j = 0; % job number
  T = 0; % arrival time of a new job
  A = 0;
  while T<Tmax;
    j=j+1;
    T=T+t;
    start(j) = max(A, arrival(j));
    S = -lambda * sum(log(rand(alpha, 1)));
    finish(j) = start(j)+S;    
     A = finish(j);
  end
  expw(i) = mean(start-arrival);
  maxw(i) = max(start-arrival);
  nr_p(i) = sum(finish>Tmax);
  
endfor
el_time = cputime - tcpu;

fprintf('a) expected waiting time E(W) is %3.2f min.\n',mean(expw));

fprintf('b) longest waiting time is %3.2f min.\n', mean(maxw));

fprintf('c) number of patients at time Tmax is %3.3f \n',mean(nr_p));

fprintf('CPU time = %f seconds \n', el_time)
