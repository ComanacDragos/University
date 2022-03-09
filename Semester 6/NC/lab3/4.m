x = -5:0.01:5;

function retval=f(x)
  retval = 1./(1+x.^2);
endfunction


function retval=compute_x_vals(n)
  retval = 0:1:n;
  retval = retval * (10/n)-5;
endfunction

function retval=compute_y_vals(n)
  retval = 0:1:n;
  retval = retval/10-5;
endfunction


hold;
for n=2:2:8
  n
  
  x_vals = compute_x_vals(n);
  plot(x, barycentric(x, x_vals, f(x_vals)));
  
  y_vals = compute_y_vals(100);
  max(abs(f(y_vals)-barycentric(y_vals, x_vals, f(x_vals))))
endfor

plot(x, f(x), "g")


legend("2", "4", "6", "8", "actual","location", "south")