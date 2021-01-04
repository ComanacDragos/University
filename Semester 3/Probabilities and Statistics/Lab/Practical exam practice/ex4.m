pkg load statistics;

X1 = [1021, 980, 1017, 988, 1005, 998, 1014, 985, 995, 1004, 1030, 1015, 995, 1023];
X2 = [1070, 970, 993, 1013, 1006, 1002, 1014, 997, 1002, 1010, 975];

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

#{
data suggests that both suppliers average out to the same mean --> A is as reliable as B and B is as reliable as A
#}