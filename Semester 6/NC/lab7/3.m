axis([0 3 0 5]);

[x, y, _] = ginput(10);

x_values = 0:0.1:3;

aprox = polyfit(x, y, 2);


plot(x, y, 'r*', x_values, polyval(aprox, x_values))