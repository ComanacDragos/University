pkg load statistics;
alpha = input("alpha= ");
tail = 'both';
X1 = [22.4, 21.7, 24.5, 23.4, 21.6, 23.3, 22.4, 21.6, 24.8, 20];
n1 = length(X1);
X2 = [17.7, 14.8, 19.6, 19.6, 12.1, 14.8, 15.4, 12.6, 14.0, 12.2];
n2 = length(X2);

#{
 H0 = means are equal
 H1 = means are not equal
 
 theta = mean1-mean2
 From a we know that the variances are equal --> std deviations are equal
#}

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

# test statistic > 0 --> higher with premium
