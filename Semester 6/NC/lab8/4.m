1;

function retval=f(x)
  retval = x.*log(x);
endfunction

function repeated_trapezium(n, a, b, f)
  h = (b-a)/n;
  x = ones(1, n+1);
  k = 0:n;
  x = a.*x + k.*h;
  retval = ((b-a)/(2*n))*(f(a) + f(b) + 2*sum(f(x(2:n))))
endfunction

#{

f(x) = x*ln(x)

f'(x) = ln(x) + 1

f''(x) = 1/x => max val on [1,2] is 1


1/(12*)

#}


eps = 1e-3;

for n=1:100
  error = 1/(12*n^2);
  if error < eps  
    n  
    break;
  endif
endfor


repeated_trapezium(n, 1, 2, @f)