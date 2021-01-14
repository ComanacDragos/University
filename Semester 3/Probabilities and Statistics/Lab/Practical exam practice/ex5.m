pkg load statistics;

X1 = [3.1, 2.9, 3.8, 3.3, 2.7, 3.0, 2.8, 2.5, 2.6, 2.0, 3.2, 2.4, 2.3, 3.1, 2.1, 3.4];
X2 = [6.9, 6.4, 4.7, 4.3, 5.1, 6.3, 5.9, 5.4, 5.3, 5.2,5.1, 5.9, 5.8, 4.9];
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

#--> data suggests that the variances are equal


[H, P, CI, STATS] = ttest2(X1, X2, 'ALPHA', alpha, 'TAIL', tail, 'VARTYPE', 'equal');

printf("The value of H is: %d\n", H);

if (H == 1)
  printf("The null hypothesis is rejected and the data suggests that the 2 means are not equal\n");
else
  printf("The null hypothesis is not rejected and the data suggests that the 2 means are equal\n");
endif

printf("RR: (-inf, %d) U (%d, inf)\n", tinv(alpha/2, n1+n2-2), tinv(1-alpha/2, n1+n2-2));
printf("P: %d\n", P);

printf("TSTATS: %d\n", STATS.tstat);

if(STATS.tstat < 0)
  printf("other employees dispose on average of more white paper per year than bank employees because tstats is positive\n");
else
  printf("bank employees dispose on average of more white paper per year than other employees tstats is negative\n");
endif