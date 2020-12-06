X = [2, 1, 3, 6,5,9,2,2];
Y = [3,2,2,5,8,8,1,1];

#a)
printf('Mean of X: %d\nMean of y: %d\n\n', mean(X), mean(Y));

#b)

printf('Variance of X: %d\nVariance of Y: %d\n\n', var(X), var(Y));

#c)

printf('cov(X,Y)= %d\n\n', cov(X,Y));

#d)

printf('Correlation coefficient: %d\n\n', corrcoef([X,Y]));