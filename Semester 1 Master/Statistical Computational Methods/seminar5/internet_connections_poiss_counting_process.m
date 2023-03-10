# algo 3.3 lecture 7

clear all;
pkg load statistics;

lambda = 5;#input('frequency lamb = ');
Tmax = 30;#input('time frame in minutes Tmax= ');

arr_times = -1/lambda * log(rand);

last_arrival = arr_times;
while last_arrival <= Tmax
  last_arrival = last_arrival - 1/lambda * log(rand);
  arr_times = [arr_times, last_arrival];
endwhile

arr_times = arr_times(1:end-1) # last will go over Tmax

step = 0.01;

t=0:step:Tmax;

Nsteps = length(t);

X = zeros(1, Nsteps);

for s=1:Nsteps
  X(s) = sum(arr_times <= t(s)); # number of arrivals by the time s
endfor 

axis([0 max(t) 0 max(X)]); hold on
title('Poisson process of arrivals')
xlabel('time');
ylabel('number of arrivals');

comet(t, X)

