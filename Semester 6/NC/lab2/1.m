l = [
  0, 0, 0, 1, 0;
  0, 0, 3/2, 0, -1/2;
  0, 5/2, 0, -3/2, 0;
  35/8, 0, -15/4, 0, 3/8
];

r = 2;
c = 2;
x = 0:0.01:1;

for n=1:r*c
    subplot(r,c,n);
    plot(x, polyval(l(n, :), x));
    title(n)
endfor
