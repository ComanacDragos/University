function a = fdt(x, f)
  m = length(f);
  a = zeros(m, m+1);
  a(:, 1) = x;
  a(:, 2) = f;
  for col=3:m+1
    for line=1:m-(col-2)
      a(line, col) = (a(line+1, col-1)-a(line, col-1))/(x(line+col-2)-x(line));
    endfor
  endfor
endfunction