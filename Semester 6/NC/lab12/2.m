1; 
pkg load optim;
function r=newton_6(x0, f)
  prev = x0;
  r = zeros(1, 6);
  for i=1:6
    current = prev - f(prev)/deriv(f, prev);
    r(i) = current;
     prev = current;
  endfor
endfunction

function r=f(E)
  r = E-0.8.*sin(E) - (2*pi)/10;
endfunction

predicted = newton_6(1, @f)

real = fzero(@f, 1)
