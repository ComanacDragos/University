pkg load statistics;

X1 = [3.1, 2.9, 3.8, 3.3, 2.7, 3.0, 2.8, 2.5, 2.6, 2.0, 3.2, 2.4, 2.3, 3.1, 2.1, 3.4]; #bank employees
X2 = [6.9, 6.4, 4.7, 4.3, 5.1, 6.3, 5.9, 5.4, 5.3, 5.2,5.1, 5.9, 5.8, 4.9]; # other employees
n1=length(X1);
n2=length(X2);
alpha = 0.05;
tail = 'both';

#{
Because the normality of the population is assumed
we can conduct a hypothesis test for the ratio of the variances of 2
populations. Because we want to see if the 2 population variances differ
we will use a 2 tail test with the following null hypothesis

H0: s1^2/s2^2 = 1

and we will check it against the following hypothesis

H1: s1^2/s2^2 != 1

#}


[H, P, CI, STATS] = vartest2(X1, X2, 'ALPHA', alpha, 'TAIL', tail);

printf("For subpoint a:\nThe value of H is: %d\n", H);

if (H == 1)
  printf("The null hypothesis is rejected and the data suggests that the 2 variances are not equal\n");
else
  printf("The null hypothesis is not rejected and the data suggests that the 2 variances are equal\n");
endif

printf("RR: (-inf, %d) U (%d, inf)\n", finv(alpha/2, n1-1, n2-1), finv(1-alpha/2, n1-1, n2-1));
printf("P: %d\n", P);

printf("TSTATS: %d\n\n\n", STATS.fstat);

#--> data suggests that the variances are equal

#{
Because the normality of the population is assumed
we can conduct a hypothesis test for the difference of the means of 2
populations. Because we want to see if the 2 population means differ
we will use a 2 tail test with the following null hypothesis

H0: m1-m2=0

and we will check it against the following hypothesis

H1: m1-m2 != 0

We also know from the previous subpoint that the populations standard deviations
seem to be equal.
#}

[H, P, CI, STATS] = ttest2(X1, X2, 'ALPHA', alpha, 'TAIL', tail, 'VARTYPE', 'equal');

printf("For subpoint b:\nThe value of H is: %d\n", H);

if (H == 1)
  printf("The null hypothesis is rejected and the data suggests that the 2 means are not equal\n");
else
  printf("The null hypothesis is not rejected and the data suggests that the 2 means are equal\n");
endif

printf("RR: (-inf, %d) U (%d, inf)\n", tinv(alpha/2, n1+n2-2), tinv(1-alpha/2, n1+n2-2));
printf("P: %d\n", P);

printf("TSTATS: %d\n", STATS.tstat); # TSTAT is the observed value of the difference of means

if(STATS.tstat < 0)
  printf("other employees dispose on average of more white paper per year than bank employees because tstats is negative\n");
else
  printf("bank employees dispose on average of more white paper per year than other employees tstats is positive\n");
endif