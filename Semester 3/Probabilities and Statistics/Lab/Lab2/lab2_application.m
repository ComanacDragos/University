pkg load statistics;

n=3;
p=0.5;
x=[0, 1, 2, 3];

#{
a) It is a binomial distribution 

PDF
  0       1       2       3
0.125   0.375   0.375   0.125

subplot(1, 2, 1);
plot(x, binopdf(x, n, p), '*');
title("PDF");

#}

#{

b) Cummulative distribution function:

  0       1       2       3
0.125    0.5   0.875      1

subplot(1, 2, 2);
stairs(x, binocdf(x, n, p));
title("CDF");

#}


# c)
disp("c)")
binopdf(0, n, p)
binocdf(n, n, p) - binopdf(1, n, p)

disp("d)")
binocdf(2, n, p)
binocdf(1, n, p)

disp("e)")

binocdf(n, n, p) - binopdf(0, n, p)
binocdf(n, n, p) - binocdf(1, n, p)

disp("f)")
# heads = -1, tails = 1

occurences = zeros(1, n + 1);
for k=1:5000
  heads = 0;
  tosses = round(rand(1, 3) *100 - 50);
  for i=1:n
    if(tosses(i) < 0)
      heads += 1;
     endif
  endfor
  occurences(heads + 1) += 1;
endfor

occurences /= 5000
binopdf(x, n, p)
plot(x, binopdf(x, n, p), '*r', x, occurences(x+1), '*b');

