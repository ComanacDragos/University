1;

function r=bisection(a0,b0,eps,N, f)
  a=a0;
  b=b0;
  if f(a)*f(b)>0
    message='no sol can be found'
    r = -1111111';
    return  
  endif
  for i=0:N
    c = (a+b)/2;
    fc = f(c);
    
    if f(a)*fc<0
      b=c;
    else
      a=c;
    endif
    
    if abs(f(c))<=eps
      r=c;
      return
    endif
  endfor
  message='no sol found'
  r = -1111111;
endfunction


function r=false_position(a0,b0,eps,N, f)
  a=a0;
  b=b0;
  if f(a)*f(b)>0
    message='no sol can be found'
    r = -1111111';
    return  
  endif
  for i=0:N
    fa = f(a);
    fb = f(b);
    
    c = (fb*a-fa*b)/(fb-fa);
    fc = f(c);
    
    if fa*fc<0
      b=c;
    else
      a=c;
    endif
    
    if abs(f(c))<=eps
      r=c;
      return
    endif
  endfor
  message='no sol found'
  r = -1111111;
endfunction

function r=f(x)
  r = (x-2).^2-log(x);
endfunction


predicted_bisection = bisection(1,2, 1e-4, 100, @f)
predicted_false_position = false_position(1,2, 1e-4, 100, @f)


real = fzero(@f, 1)

err_bisection = abs(real-predicted_bisection)

err_false_position = abs(real-predicted_false_position)