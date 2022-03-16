x_vals = linspace(0, 6, 13)

f_vals = exp(sin(x_vals));


x = 0:0.01:6;


plot(x_vals, exp(sin(x_vals)), '*', x, exp(sin(x)),'r', x, newton(x, x_vals, f_vals), 'b')
