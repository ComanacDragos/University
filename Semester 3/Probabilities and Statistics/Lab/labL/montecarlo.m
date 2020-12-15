pkg load statistics;

a=-2;
b=2;

n= 1000;

x = normrnd(a,b,1,n);

function y = f(x)
 y = exp(-x*x)
endfunction

integral(f, a,b)