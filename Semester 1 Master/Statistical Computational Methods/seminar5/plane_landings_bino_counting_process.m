# algo 3.6 lecture 6

clear all;
pkg load statistics;

NB = 60;#input('len of sample path= ');
p = 0.1;#input('prob. of success (arrival) = ');
X = zeros(1, NB);

X(1) = (rand<p);

for t=2:NB
  X(t) = X(t-1) + (rand<p);
endfor

X

clf
Del = 1;#input(' frame zise (in seconds) = ');
axis([0 NB 0 max(X)]);

hold on;

title('Binomial process of arrivals');
xlabel('time');
ylabel('nr of arrivals');

for t=1:NB
  plot(t, X(t), '*', 'MarkerSize', 8); hold on
  pause(Del)
endfor

hold off
