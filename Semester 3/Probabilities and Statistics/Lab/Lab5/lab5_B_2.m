pkg load statistics;

alpha = 1 - input('Give 1-alpha: ');

X1 = [22.4, 21.7, 24.5, 23.4, 21.6, 23.3, 22.4, 21.6, 24.8, 20];

X2 = [17.7, 14.8, 19.6, 19.6, 12.1, 14.8, 15.4, 12.6, 14.0, 12.2];

#a)
n1 = length(X1);
n2 = length(X2);
sp = sqrt(((n1-1)*var(X1)+(n2-1)*var(X2))/(n1+n2-2));
left = mean(X1) - mean(X2) - tinv(1-alpha/2, n1+n2-2)*sp*sqrt(1/n1 + 1/n2);
right = mean(X1) - mean(X2) + tinv(1-alpha/2, n1+n2-2)*sp*sqrt(1/n1 + 1/n2);

printf('For a the ci for the difference is (%d, %d)\n', left, right);

#b)
n1 = length(X1);
n2 = length(X2);

c = (var(X1)/n1)/(var(X1)/n1 + var(X2)/n2);
n = 1/(c^2/(n1-1) + ((1-c)^2)/(n2-1));

left = mean(X1) - mean(X2) - tinv(1-alpha/2, n)*sqrt(var(X1)/n1 + var(X2)/n2);
right = mean(X1) - mean(X2) + tinv(1-alpha/2, n)*sqrt(var(X1)/n1 + var(X2)/n2);

printf('For b the ci for the difference is (%d, %d)\n', left, right);

#c)

left = 1/finv(1-alpha/2, n1-1, n2-1) * (var(X1)/var(X2));
right = 1/finv(alpha/2, n1-1, n2-1) * (var(X1)/var(X2));

printf('For c the ci for the difference is (%d, %d)\n', left, right);
