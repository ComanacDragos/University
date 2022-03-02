#{
  
  Divided differences table
  
xi  fi  D1f   D2f   D3f  
2   4    2    1/4   -1/8
4   8    3    -1/2
6   14   1
8   16

D1f (xi) = (f(xi+1)-f(xi))/(xi+1-xi)

Dkf (xi) = (Dk-1f(xi+1)-Dk-1f(xi))/(xi+k-xi)

#}


function a = fdt(x, f)
  m = length(f);
  a = zeros(m, m+1)
  a(:, 1) = x;
  a(:, 2) = f;
  for col=3:m+1
    for line=1:m-(col-2)
      a(line, col) = (a(line+1, col-1)-a(line, col-1))/(x(line+col-2)-x(line));
    endfor
  endfor
endfunction


fdt([2 4 6 8], [4 8 14 16])