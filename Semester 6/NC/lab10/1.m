#a
A =  [10 7 8 7;
      7 5 6 5;
      8 6 10 9;
      7 5 9 10];
      
b = [32;23;33;31;];

x = A\b

conditioning_number = cond(A)


#b

b_hat = [32.1;22.9;33.1;30.9];

x_hat = A\b_hat

input_err = norm(b-b_hat)/norm(b)
output_err = norm(x-x_hat)/norm(x)

ratio = output_err/input_err

#c

A_hat = [
10 7 8.1 7.2;
7.08 5.04 6 5;
8 5.98 9.89 9;
6.99 4.99 9 9.98 ];

x_hat = A_hat\b

input_err = norm(A-A_hat)/norm(b)
output_err = norm(x-x_hat)/norm(x)

ratio = output_err/input_err

