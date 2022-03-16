#{
Neville

Qi0 = f(xi)

Qij = ((xi-x)*Qi-1,j-1 - (x-xi-j)* Qi,j-1)/(xi-xi-j)


#}

1;

function retval=neville(x, x_vals, f_vals)
  m = length(x_vals);
  table = zeros(m, m);
  table(:, 1) = f_vals;
 
  for i=2:m
    for j=2:i
      table(i, j) = ((x_vals(i) - x) * table(i-1, j-1) + (x-x_vals(i-j+1))*table(i, j-1))/(x_vals(i)-x_vals(i-j+1));   
    endfor
   endfor
   table;
   retval = table(m,m);
endfunction


#a
x_vals = [-2, -1, 0, 1, 2];

f1 = 3.^x_vals;

actual_val = sqrt(3)

a_pred = neville(1/2, x_vals, f1)

x_vals = [0, 1, 2, 4, 5];

f2 = sqrt(x_vals);

b_pred = neville(3, x_vals, f2)