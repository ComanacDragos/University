pkg load statistics

m = input("Degrees of freedom: ");
n = input("Degrees of freedom: ");


disp("a)");

fcdf(0, m, n)
1 - fcdf(0, m, n) + fpdf(0, m, n)

disp("b)");

v = fcdf(1, m, n) - fcdf(-1, m, n)
1 - v + fpdf(1, m, n) + fpdf(-1, m, n)

disp("c)");

alpha = input("alpha: ");
finv(alpha, m, n)

disp("d)");

beta = input("beta: ");
finv(1 - beta, m, n)