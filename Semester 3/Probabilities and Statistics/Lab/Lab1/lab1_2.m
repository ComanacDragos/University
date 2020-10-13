x=0:0.01:3;

y1 = x.^5/10;
y2 = x.*sin(x);
y3 = cos(x);

subplot(2,2,1);
plot(x, y1, "--r", x, y2, ":y", x, y3, "-.g");
title("First plot");
legend("x^5/10", "x*sin(x)", "cos(x)");

subplot(2,2,2);
plot(x, y1, "--r");

subplot(2,2,3);
plot(x,y2, ":y");

subplot(2,2,4);
plot(x,y3,"-.g");