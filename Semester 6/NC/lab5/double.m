function retval = double(x)
  retval = zeros(1, length(x));
  for i=1:length(x)
    retval(2*i-1) = x(i);
    retval(2*i) = x(i);
  endfor
endfunction
