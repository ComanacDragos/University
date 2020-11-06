pkg load statistics

n = input("Degrees of freedom: ");


disp("a)");

chi2cdf(0, n)
1 - chi2cdf(0, n) + chi2pdf(0, n)

disp("b)");

v = chi2cdf(1, n) - chi2cdf(-1, n)
1 - v + chi2pdf(1, n) + chi2pdf(-1, n)

disp("c)");

alpha = input("alpha: ");
chi2inv(alpha, n)

disp("d)");

beta = input("beta: ");
chi2inv(1 - beta, n)