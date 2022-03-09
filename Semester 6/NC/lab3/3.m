x_vals = linspace(0, 10, 21);

x = 0:0.01:10;

function retval=f(x)
  retval = (1+cos(pi*x))./(1+x);
endfunction


plot(x, f(x), "r", x, barycentric(x, x_vals, f(x_vals)));