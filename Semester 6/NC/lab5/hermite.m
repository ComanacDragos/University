function retval = hermite(x, x_vals, f_vals, df_vals)
  retval = f_vals(1);
  f = 1;
  table = fdt(x_vals, f_vals, df_vals);
  z = double(x_vals);
  for i=1:length(z)-1
    f = f*(x-z(i));
    retval = retval + f.*table(1, i+2);
  endfor
endfunction