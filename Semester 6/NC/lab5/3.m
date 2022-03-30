x = -5:0.1:5;
x_vals = linspace(-5, 5, 15);
f_vals = sin(2*x_vals);
df_vals = 2*cos(2*x_vals);

f_aprox = zeros(1, length(x));

for i=1:length(x)
  f_aprox(i) = hermite(x(i), x_vals, f_vals, df_vals);
endfor

plot(x, sin(2*x), 'r', x, f_aprox, 'b')
legend('actual', 'approx')