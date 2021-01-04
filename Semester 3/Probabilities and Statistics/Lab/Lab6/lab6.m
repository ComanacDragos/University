pkg load statistics;

#{
ask the user for your alpha

input the data in a vector x and if you wish
take a var n to be the length of x

using comments explain in 1,2,3 lines what
is the null hypothesis / this is a sort of test

print what kind of test for what parameter it is
and in which case

mean0 to be asked from the input


call the z test function

using the information from the test.pdf inside here
you implement what quantile you need check how each quantiles
are used

after we have RR print on screen the value of H
from the ztest call

after that create an if clause
if h=1
    print null hyp is rejected and 
    print a screen a msg:
    the data suggest that the data suggest that the standard
    is not met
  else
    print null hyp is not rejected 
    the data suggests that the standard is met
endif

using fprintf print 3 messages
1. The RR is:
2. The value of the TS
3. The P-value of the test is:
#}
# TS0 = observed value of the test statistic


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
  



