pkg load statistics

p = input('Give p= ');
n = input('Give n= ');
N = input('Give N= ');


X = zeros(1,N);
for i=1:N
  U = unifrnd(0,1, 1, n);
  X(i) = sum(U<p);
endfor

x=1:n;

U_X = unique(X);
N_X = hist(X, length(U_X));
F_X = N_X/N;

plot(x, binopdf(x,n,p), 'g*');
hold on;
plot(U_X, F_X, 'b*');