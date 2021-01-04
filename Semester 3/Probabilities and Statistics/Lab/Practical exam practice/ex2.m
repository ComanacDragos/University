pkg load statistics;

X1 = [46, 37,39, 48,47,44,35,31,44,37];
X2 = [35, 33, 31, 35,34,30,27, 32,31,31];


n1=length(X1);
n2=length(X2);
alpha = 0.05;
tail = 'both';

#{
2 tailed test

H0: s1/s2 = 1

#}


[H, P, CI, STATS] = vartest2(X1, X2, 'ALPHA', alpha, 'TAIL', tail);

printf("The value of H is: %d\n", H);

if (H == 1)
  printf("The null hypothesis is rejected and the data suggests that the 2 variances are not equal\n");
else
  printf("The null hypothesis is not rejected and the data suggests that the 2 variances are equal\n");
endif

printf("RR: (-inf, %d) U (%d, inf)\n", finv(alpha/2, n1-1, n2-1), finv(1-alpha/2, n1-1, n2-1));
printf("P: %d\n", P);

printf("TSTATS: %d\n\n\n", STATS.fstat);

#--> data suggests that the variances are not equal

c = (var(X1)/n1)/(var(X1)/n1 + var(X2)/n2);
n = 1/(c^2/(n1-1) + ((1-c)^2)/(n2-1));

left = mean(X1) - mean(X2) - tinv(1-alpha/2, n)*sqrt(var(X1)/n1 + var(X2)/n2);
right = mean(X1) - mean(X2) + tinv(1-alpha/2, n)*sqrt(var(X1)/n1 + var(X2)/n2);

printf('For b the ci for the difference is (%d, %d)\n', left, right);
