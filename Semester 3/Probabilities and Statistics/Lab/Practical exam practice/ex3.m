pkg load statistics;

X = [3.26,1.89, 2.42,2.03,3.07,2.95,1.39, 3.06,2.46,3.35, 1.56,1.79,1.76,3.82,2.42,2.96];

alpha = 0.05;


s=std(X);
left = mean(X) - s/(sqrt(length(X))) * tinv(1-alpha/2, length(X)-1);
right = mean(X) - s/(sqrt(length(X))) * tinv(alpha/2, length(X)-1);

printf('For a) the interval is [%d, %d]\n\n', left, right);


#{
  b)
  

#}

alpha = 0.01;
tail = 'left';
mean0 = 3;

[H, P, CI, STATS] = ttest(X, mean0, 'ALPHA', alpha, 'TAIL', tail);


printf("The value of H is: %d\n", H);

if (H == 1)
  printf("The null hypothesis is rejected and the data suggests that the avg is not smaller than 3\n");
else
  printf("The null hypothesis is not rejected and the data suggests that the avg is smaller than 3\n");
endif


printf("The rejection region is (%d, inf)\n", norminv(1-alpha));
printf("The value of ZVAl is:%d\nThe value of P is:%d\n", STATS.tstat, P);
