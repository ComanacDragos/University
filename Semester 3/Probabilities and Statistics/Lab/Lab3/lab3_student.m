pkg load statistics

n = input("Degrees of freedom: ");


disp("a)");

tcdf(0, n)
1 - tcdf(0, n) + tpdf(0, n)

disp("b)");

v = tcdf(1, n) - tcdf(-1, n)
1 - v + tpdf(1, n) + tpdf(-1, n)

disp("c)");

alpha = input("alpha: ");
tinv(alpha, n)

disp("d)");

beta = input("beta: ");
tinv(1 - beta, n)