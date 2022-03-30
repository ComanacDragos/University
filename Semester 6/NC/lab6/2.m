[x, y, _] = ginput(5);

x_vals = linspace(x(1), x(end), 50);
plot(x, y, 'r*', x_vals, spline(x, y, x_vals))