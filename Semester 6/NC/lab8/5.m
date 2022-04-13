1;

function retval=f(x)
  retval = 1./(4+sin(20.*x));
endfunction

function retval=repeated_simpson(n, a,b,f)
  h = (b-a)/n;
  x = ones(1, n+1);
  k = 0:n;
  x = a.*x + k.*h;
  
  sum1 = 0;
  
  l = n+1;
  for k=2:l
    sum1 = sum1 + f((x(k-1)+x(k))/2);
  endfor
  
  sum2=0;
  for k=2:n
    sum2 = sum2+f(x(k));  
  endfor
  retval = ((b-a)/(6*n))*(f(a)+f(b) + 4*sum1+2*sum2);
endfunction


n_10 = repeated_simpson(10, 0, pi, @f)
n_30 = repeated_simpson(30, 0, pi, @f)