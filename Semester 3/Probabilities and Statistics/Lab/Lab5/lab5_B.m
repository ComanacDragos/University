pkg load statistics;

alpha = 1 - input('Give 1-alpha: ');



X =[7, 7, 4, 5, 9, 9,4, 12, 8, 1, 8, 7,3, 13, 2, 1, 17, 7,12, 5, 6, 2, 1, 13,14, 10, 2, 4, 9, 11,3, 5, 12, 6, 10, 7];

#a)
stdv = 5;
left = mean(X) - stdv/(sqrt(length(X))) * norminv(1-alpha/2);
right = mean(X) - stdv/(sqrt(length(X))) * norminv(alpha/2);

printf('For a) the interval is [%d, %d]\n\n', left, right);

#b)

s=std(X);
left = mean(X) - s/(sqrt(length(X))) * tinv(1-alpha/2, length(X)-1);
right = mean(X) - s/(sqrt(length(X))) * tinv(alpha/2, length(X)-1);

printf('For b) the interval is [%d, %d]\n\n', left, right);

#c)


ssq=var(X);
left = (length(X)-1)*ssq/chi2inv(1-alpha/2, length(X)-1);
right = (length(X)-1)*ssq/chi2inv(alpha/2, length(X)-1);

printf('For c) the interval is [%d, %d]\n\n', left, right);

printf('For c) the interval for stdv is [%d, %d]\n\n', sqrt(left), sqrt(right));
