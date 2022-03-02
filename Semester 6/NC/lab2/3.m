#{
  use previous form for
  x^i/i!
#}

function retval = taylor(n)
   retval = [1];
   f = 1;
   for i=1:n
    f = i*f;
    retval(end+1) = 1/f;
   endfor
   retval = flip(retval);
endfunction


x = -1:0.01:3;

n = 6;

hold on;
for i=1:6
 plot(x, polyval(taylor(i), x));
endfor
