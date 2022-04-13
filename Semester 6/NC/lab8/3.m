1;

function repeated_trapezium(n, a, b, f)
  h = (b-a)/n;
  x = ones(1, n+1);
  k = 0:n;
  x = a.*x + k.*h;
  
  retval = ((b-a)/(2*n))*(f(a) + f(b) + 2*sum(f(x(2:n))))
endfunction


function retval=f(x, p, r)
  retval = sqrt(1-((p/r)^2 ).* sin(x));  
endfunction


function retval=aux(x)
  r=110;
  p=75;
  retval = f(x, p,r); 
endfunction

n = 5;
r=110;
p=75;


repeated_trapezium(n, 0, 2*pi, @aux)
(60*r/(r^2-p^2)) * repeated_trapezium(n, 0, 2*pi, @aux)