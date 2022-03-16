function retval=newton(x, x_vals, f_vals)
  retval = ones(1, length(x))*f_vals(1);
  f = ones(1, length(x));
  table = fdt(x_vals, f_vals);
  
  for i=1:length(x_vals)-1
    f = f.*(x-x_vals(i));
    retval = retval + f.*table(1, i+2);
  endfor
endfunction
