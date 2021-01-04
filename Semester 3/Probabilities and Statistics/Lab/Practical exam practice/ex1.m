pkg load statistics;

X1 = [4.6,0.7,4.2,1.9,4.8,6.1,4.7,5.5,5.4];
X2 = [2.5,1.3,2.0,1.8,2.7,3.2,3.0,3.5,3.4];

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


[H, P, CI, STATS] = ttest2(X1, X2, 'ALPHA', alpha, 'TAIL', tail, 'VARTYPE', 'unequal');

printf("The value of H is: %d\n", H);

if (H == 1)
  printf("The null hypothesis is rejected and the data suggests that the 2 means are not equal\n");
else
  printf("The null hypothesis is not rejected and the data suggests that the 2 means are equal\n");
endif

printf("RR: (-inf, %d) U (%d, inf)\n", tinv(alpha/2, n1+n2-2), tinv(1-alpha/2, n1+n2-2));
printf("P: %d\n", P);

printf("TSTATS: %d\n", STATS.tstat);

#{
  data suggests that steel pipes lose more heat than glass pipes
#}