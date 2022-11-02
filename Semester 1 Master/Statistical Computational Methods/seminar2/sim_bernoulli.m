clear all;

function X=bernoulli_dist(p)
  U = rand;
  X = (U<p);
endfunction

p = input("p in (0,1) = ");
N = input('nr of simulations = ');
#bernoulli_dist(p)

X = zeros(1, N);
for i=1:N
   U = rand;
   X(i) = (U < p);
endfor

UX = unique(X)
nX = hist(X, length(UX));

relfreq = nX/N
