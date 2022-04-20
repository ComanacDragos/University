1;

function retval = simpson(a, b, f)
  retval = ((b-a)/6) * (f(a) + 4*f((a+b)/2) + f(b));
endfunction

function retval=adquad(a,b,eps,f)
  i1 = simpson(a,b,f);
  mid = (a+b)/2;
  i2 = simpson(a, mid) + simpson(mid, b);
  if abs(i1-i2)<15*eps
    retval = i2;
    return
  else
     retval = adquad(a, mid, eps/2, f) + adquad(mid, b, eps/2, f);   
  endif
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

function retval = f(x)
  retval = (100./(x.^2)) * sin(10./x);
endfunction

pred = adquad(1,3,1e-4, @f)

pred_simp_50 = repeated_simpson(50, 1,3,@f)
pred_simp_100 = repeated_simpson(100, 1,3,@f)
