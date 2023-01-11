clear all
pkg load statistics

Nm = 30;#input('length of sample path (of Markov chain');
N = 10000#input(' nr  of simulations = ')
#{
X = zeros(1, Nm); 
P0 = [0.2 0.8];
P = [0.7 0.3; 0.4 0.6];

P1(1, :) = P0;

for t=1:Nm
  U = rand;
  X(t) = 1 * (U<P0(1)) + 2 * (U>=P0(1));
  P1(t+1, :) = P1(t, :) * P;
  P0 = P(X(t),:);
endfor

X

i_change = [find(X(1:end-1) ~= X(2:end)), Nm] # ~= not equal

longstr(1) = i_change(1);

for i=2:length(i_change)
  longstr(i) = i_change(i) - i_change(i-1);
endfor

longstr

#longstr = [i_change(1), i_change(2:end)-i_change(1:end-1)]

if(X(1) == 1)
   sunny = longstr(1:2:end);
   rainy = longstr(2:2:end);
else
   sunny = longstr(2:2:end);
   rainy = longstr(1:2:end);
end

max_sunny = max(sunny)
max_rainy = max(rainy)
#}


max_sunny = zeros(1, N);
max_rainy = zeros(1, N);

for j=1:N
    X = zeros(1, Nm); 
    P0 = [0.2 0.8];
    P = [0.7 0.3; 0.4 0.6];

    P1(1, :) = P0;

    for t=1:Nm
      U = rand;
      X(t) = 1 * (U<P0(1)) + 2 * (U>=P0(1));
      P1(t+1, :) = P1(t, :) * P;
      P0 = P(X(t),:);
    endfor

    i_change = [find(X(1:end-1) ~= X(2:end)), Nm]; # ~= not equal

    longstr(1) = i_change(1);

    for i=2:length(i_change)
      longstr(i) = i_change(i) - i_change(i-1);
    endfor

    #longstr = [i_change(1), i_change(2:end)-i_change(1:end-1)]

    if(X(1) == 1)
       sunny = longstr(1:2:end);
       rainy = longstr(2:2:end);
    else
       sunny = longstr(2:2:end);
       rainy = longstr(1:2:end);
    end

    max_sunny(j) = max(sunny);
    max_rainy(j) = max(rainy);
endfor


fprintf(' \n prob of drought is %1.4f\n', mean(max_sunny>=7))

fprintf(' prob of flooding is %1.4f\n', mean(max_rainy>=7))

