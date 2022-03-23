function a = fdt(x, f, df)
  m = 2*length(f);
  a = zeros(m, m+1); 
  a(:, 1) = double(x);
  a(:, 2) = double(f);
  for i=1:m/2
    a(2*i-1, 3) = df(i);
    line = 2*i;
    col = 3;
    if line == m
      break
    endif
    a(line, col) = (a(line+1, col-1)-a(line, col-1))/(a(line+col-2, 1)-a(line, 1));

  endfor

  for col=4:m+1
    for line=1:m-(col-2)
      a(line, col) = (a(line+1, col-1)-a(line, col-1))/(a(line+col-2, 1)-a(line, 1));
    endfor
  endfor
endfunction