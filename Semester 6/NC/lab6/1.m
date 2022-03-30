x = [0, pi/2, pi, 3*pi/2, 2*pi];
y = sin(x);

#a

actual_val = sin(pi/4)
natural = spline(x, y, pi/4)
clamped = spline(x, [cos(0), y, cos(2*pi)], pi/4)


#b

x_vals = 0:0.1:2*pi;
plot(x_vals, sin(x_vals), x_vals, spline(x, y, x_vals), x_vals, spline(x, [cos(0), y, cos(2*pi)], x_vals))
legend('actual', 'natural', 'clamped')