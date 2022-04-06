t = [0 10 20 30 40 60 80 100];
p = [0.0061 0.0123 0.0234 0.0424 0.0738 0.1992 0.4736 1.0133];


degree1 = polyfit(t, p, 1);
degree2 = polyfit(t, p, 2);

degree1_value = polyval(degree1, 45)
degree1_error = abs(degree1_value - 0.095848)

degree2_value = polyval(degree2, 45)
degree2_error = abs(degree2_value - 0.095848)


x = 0:0.1:100;

lagrange = polyfit(t,p, length(t)-1);
plot(t, p, 'r*', x, polyval(degree1, x), x, polyval(degree2, x), x, polyval(lagrange, x))

legend('points', 'degree1', 'degree2', 'lagrange')