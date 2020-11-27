p = 0.9;
k = 10;
m = 1000;
n = 5

final = [];

for j = 1: m
  poz = 0;
  LocCurent = 0;
  for i = 1:K
    X = rand;
    if X < Prob
      LocCurent = mod(LocCurent + 1, n);
    else
      LocCurent = mod(LocCurent - 1, n);
    end
  endfor
  
  final = [final, LocCurent];
endfor


N=histc(final, 0:n-1)
bar(0:n-1, N, 'hist', 'FaceColor', 'b' );