1; 
pkg load optim;
function r=newton(x0, eps, N, f)
  prev = x0;
  for i=0:N
    current = prev - f(prev)/deriv(f, prev);
    
    if abs(current-prev)<=eps
      r = current;
      return
     endif
     prev = current;
  endfor
  message='no sol found'
  r = -1111111
endfunction

function r=f(x)
  r = x-cos(x);
endfunction

predicted = newton(pi/4, 1e-4, 100, @f)


real = fzero(@f, pi/4)


err = abs(real-predicted)