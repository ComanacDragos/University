alpha = input("alpha= ");
mean0 = input("mean0= ");
tail = "right";
X =[7, 7, 4, 5, 9, 9,4, 12, 8, 1, 8, 7,3, 13, 2, 1, 17, 7,12, 5, 6, 2, 1, 13,14, 10, 2, 4, 9, 11,3, 5, 12, 6, 10, 7];
n = length(X);

#{
The null hypothesis states that the efficency standard
is not met if the average of the size is less than 5.5.
H1 on avg the number of files exceeds 5.5 --> right tail
#}

fprintf("This is a hypothesis test with unknown sigma and for theta = mean\n");

[H, P, CI, STATS] = ttest(X, mean0, 'ALPHA', alpha, 'TAIL', tail);


printf("The value of H is: %d\n", H);

if (H == 1)
  printf("The null hypothesis is rejected and the data suggests that the avg exceeds the standard\n");
else
  printf("The null hypothesis is not rejected and the data suggests that the data does not exceed the standard\n");
endif


printf("The rejection region is (%d, inf)\n", norminv(1-alpha));
printf("The value of ZVAl is:%d\nThe value of P is:%d\n", STATS.tstat, P);
  



