pkg load statistics;

n=3;
p=0.5;
x=[0, 1, 2, 3];

#{
a) It is a binomial distribution 

PDF
  0       1       2       3
0.125   0.375   0.375   0.125

#}

subplot(1, 2, 1);
plot(x, binopdf(x, n, p), '*');
title("PDF");

#{

b) Cummulative distribution function:

  0       1       2       3
0.125    0.5   0.875      1


#}

subplot(1, 2, 2);
stairs(x, binocdf(x, n, p));
title("CDF");

# c)
disp("c)")
pdf = binopdf(x, n, p);
cdf = binocdf(x, n, p);
disp(cdf(1))
disp(pdf(1) + pdf(3) + pdf(4))


