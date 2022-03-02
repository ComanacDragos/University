#{
function that computes the Chebyshev
  pol I of order n
#}

function retval = chebyshev(n, x)
   if n==0
     retval = 1;
     return
   endif
   if n==1
     retval = x;
     return
   endif
  retval = 2*x.*chebyshev(n-1,x) - chebyshev(n-2,x);
endfunction


x = -1:0.01:1;

n=4;

hold on;
for i=1:n
  i
  plot(x, chebyshev(i,x));
endfor
