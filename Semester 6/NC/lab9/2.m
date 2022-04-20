1;

function retval = romberg(a, b, eps, f)
  prev = ((b-a)/2)*(f(a) + f(b));
  current = prev;
  h = b-a;
  p = 1;
  do
    prev = current;  
    p = p*2;
    
    sum = 0;
    n = p/2;
    for j=1:n
      sum = sum + f((a+(2*j-1)/p)*h);    
    endfor
    
    current = (1/2) * prev + (h/p)*sum;
  until(abs(current-prev)<=eps)
  retval = current;  
endfunction

function retval=repeated_trapezium(n, a, b, f)
  h = (b-a)/n;
  x = ones(1, n+1);
  k = 0:n;
  x = a.*x + k.*h;
  
  retval = ((b-a)/(2*n))*(f(a) + f(b) + 2*sum(f(x(2:n))));
endfunction

function retval = aitken(a,b,eps,f)
  m = containers.Map("KeyType", "uint64", "ValueType", "any");
  m(1) = [repeated_trapezium(1,a,b,f)];
  i=1;
  p_2=1;
  do
    i = i+1;
    row = zeros(1,i);
    p_2 = p_2*2;
    p_4 = 1 ;   
    for j=1:i
      p_4 = p_4/4;
      if j==1
        row(j) = repeated_trapezium(p_2,a,b,f);       
      else
        row(j) = (p_4*m(i-1)(j-1) - row(j-1))/(p_4-1);
      endif
    endfor
    m(i) = row;
  until (abs(m(i)(i)-m(i-1)(i-1))<=eps)
  retval = m(i)(i);
endfunction

function retval = f(x)
  retval = 2./(1+x.^2);
endfunction

pred_a = romberg(0, 1, 1e-4, @f)

pred_b = aitken(0, 1, 1e-4, @f)



