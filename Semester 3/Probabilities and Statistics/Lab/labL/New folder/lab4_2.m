K = 10;
Prob = 0.7;
LocCurent = 0;
vector = repmat(0,1,K);
n = 5;

for i = 1:K
  X = rand
  if X < Prob
    LocCurent = mod(LocCurent + 1, n);
  else
    LocCurent = mod(LocCurent - 1, n);
  end
  
  vector(i) = LocCurent;
    
endfor

vector

0:n