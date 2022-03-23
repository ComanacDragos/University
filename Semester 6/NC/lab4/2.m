x = [1,2,3,4,5];
y = [22,23,25,30,28];

pred = newton(2.5, x, y)


fine_x = 1:0.01:5;
plot(x, y,'r*', fine_x,  newton(fine_x, x, y))