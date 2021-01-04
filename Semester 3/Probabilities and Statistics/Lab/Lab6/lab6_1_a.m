alpha = input("alpha= ");
mean0 = input("mean0= ");
tail = "left";
sigma = 5;
X =[7, 7, 4, 5, 9, 9,4, 12, 8, 1, 8, 7,3, 13, 2, 1, 17, 7,12, 5, 6, 2, 1, 13,14, 10, 2, 4, 9, 11,3, 5, 12, 6, 10, 7];
n = length(X);

#{
The null hypothesis states that the efficency standard
is not met if the average of the size is less than 9.
#}

fprintf("This is a hypothesis test with known sigma and for theta = mean\n");

[H, P, CI, ZVAL] = ztest(X, mean0, sigma, 'ALPHA', alpha, 'TAIL', tail);


printf("The value of H is: %d\n", H);

if (H == 1)
  printf("The null hypothesis is rejected and the data suggests that the standard is not met\n");
else
  printf("The null hypothesis is not rejected and the data suggests that the standard is met\n");
endif


printf("The rejection region is (-inf, %d)\n", norminv(alpha));
printf("The value of ZVAl is:%d\nThe value of P is:%d\n", ZVAL, P);
  



