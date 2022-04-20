1;

function retval=rectangle(a,b,f)
    retval = (b-a)*f((a+b)/2);
endfunction



function retval = f(x)
  retval = exp(-x.^2);
endfunction


pred_a = rectangle(1, 1.5, @f)


x = 1:0.1:1.5;
a = 1;
b = 1.5;
plot(x, f(x), [a, a, b, b, a], [0, f((a+b)/2), f((a+b)/2), 0, 0])

function retval=repeated_rectangle(a,b,n,f)
  x = zeros(1, n);
  
  x(1) = a + (b-a)/(2*n);
  for i=2:n
    x(i) = x(1) + (i-1)*(b-a)/n;
  endfor
  
  retval = ((b-a)/n) * sum(f(x));
endfunction

pred_150 = repeated_rectangle(1,1.5,150, @f)

pred_500 = repeated_rectangle(1,1.5,500, @f)
