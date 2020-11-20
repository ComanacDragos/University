pkg load statistics

p = input('Give p= ');
n = input('Give n= ');

U = unifrnd(0,1, 1, n);

X = zeros(1,n);
#X=(U<p)
for i = 1:n
   if (U(i) < p)
      X(i) = 1;
   else
      X(i) = 0;
   endif
endfor

U_X = unique(X);
N_X = hist(X, length(U_X));
F_X = N_X/n