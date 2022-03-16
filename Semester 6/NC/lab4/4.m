#{
Aitken algorithm


x0  f00
x1  f10 f11
.   . 
.   .
xm  fm0 fm1 .. fmm

fi0 = f(xi)

fii = (Lif)(x)

fi,j+1 = 1/(xi-xj) * determinant fjj xj-x fij xi-x
i = 1.m
j = 0..i-1

stop criterion
|fii - fi-1,i-1| <= eps

sort the nodes wrt to the distance of x to the nodes
|xi-x| <= |xj-x| i<j
#}

1;

function retval=aitken(x, x_vals, f_vals, eps)
  [_, I] = sort(abs(x-x_vals));
  x_vals=x_vals(I);
  f_vals = f_vals(I);
 
  m = length(x_vals);
  table = zeros(m, m);
  table(:, 1) = f_vals;
  
  for i=2:m
    for j=1:i-1
      table(i, j+1) = 1/(x_vals(i)-x_vals(j)) * (table(j,j) * (x_vals(i)-x) - table(i,j) * (x_vals(j)-x));
      if i==j+1
        if abs(table(i, j+1) - table(i-1, j)) <= eps
          table
          retval=table(i, j+1);
          return;
        endif
      endif        
    endfor
  endfor
  table
  error = 'give more points'
  retval = table(m, m);
endfunction

x = [81, 100, 121, 144, 169];
f = sqrt(x)
pred = aitken(115, x, f, 1e-3)

actual = sqrt(115)