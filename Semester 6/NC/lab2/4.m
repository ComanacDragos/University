#{
 
 Finite differences table
 
fi  dhf1  dhf2  dhf3  dhf4  
0    2      2     2    -11
2    4      4    -9
6    8     -5
14   3
17
 
 
 a(2,3) = a(3,2)-a(2,2)
#}

function a = fdt(f)
  m = length(f);
  a = zeros(m, m)
  a(:, 1) = f;
  for col=2:m
    for line=1:m-(col-1)
      a(line, col) = a(line+1, col-1)-a(line, col-1);
    endfor
  endfor
endfunction


x = zeros(1, 7);
h=0.25;

for i=1:7
  x(i) = 1+(i-1)*h;
endfor

f = sqrt(5*x.^2+1);
f = f';

#fdt([0 2 6 14 17])
fdt(f)