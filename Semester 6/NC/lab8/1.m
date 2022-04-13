1;
function retval = trapezium(a,b, f)
  retval = ((b-a)/2) * (f(a) + f(b));
endfunction

function retval = simpson(a, b, f)
  retval = ((b-a)/6) * (f(a) + 4*f((a+b)/2) + f(b));
endfunction

function retval = f(x)
  retval = 2./(1+x.^2);
endfunction


x = 0:0.1:1;


trapezium_aprox = trapezium(0, 1, @f)
simpson_aprox = simpson(0, 1, @f)


plot(x, f(x), [0, 0, 1, 1], [0, f(0), f(1), 0], [0, 1], [0,0])