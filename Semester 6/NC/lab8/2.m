1;

function retval = double_integral(a,b,c,d, f)
  factor = (b-a)*(d-c)/16;
  first_sum = f(a,c)+f(a,d)+f(b,c)+f(b,d);
  second_sum = 2*f((a+b)/2, c) + 2*f((a+b)/2, d) + 2*f(a, (c+d)/2);
  third_sum = 2*f(b, (c+d)/2) + 4*f((a+b)/2, (c+d)/2);
  
  retval = factor*(first_sum + second_sum + third_sum);
endfunction


function retval = f(x, y)
  retval = log(x+2*y);
endfunction

aprox = double_integral(1.4, 2, 1, 1.5, @f)
