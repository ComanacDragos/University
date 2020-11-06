pkg load statistics

mean = input("Mean: ");
stdv = input("Stdv: ");

disp("a)");

normcdf(0, mean, stdv)
1 - normcdf(0, mean, stdv) + normpdf(0, mean, stdv)

disp("b)");

v = normcdf(1, mean, stdv) - normcdf(-1, mean, stdv)
1 - v + normpdf(1, mean, stdv) + normpdf(-1, mean, stdv)

disp("c)");

alpha = input("alpha: ");
norminv(alpha, mean, stdv)

disp("d)");

beta = input("beta: ");
norminv(1 - beta, mean, stdv)