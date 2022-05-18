1; 
pkg load optim;
function r=newton(x0, x1, eps, N, f)
  prev = x1;
  prevprev = x0;
  for i=0:N
    d = (f(prev)-f(prevprev))/(prev-prevprev);
    current = prev - f(prev)/d;
    
    if abs(current-prev)<=eps
      r = current;
      return
     endif
     prevprev = prev;
     prev = current;
  endfor
  message='no sol found'
  r = -1111111
endfunction

function r=f(x)
  r = x.^3-x.^2-1;
endfunction


predicted = newton(1,2, 1e-4, 100, @f)


real = fzero(@f, 1)

err = abs(real-predicted)