pkg load statistics;

n=input('Give number of trials: ');
p=input('Give probability: ');
x=[0:n];


subplot(1, 2, 1);
plot(x, binopdf(x, n, p), '*');
title("PDF");

subplot(1, 2, 2);
stairs(x, binocdf(x, n, p));
title("CDF");