function retval = barycentric(x, x_vals, f_vals)
    m = length(x_vals);
    A = ones(1,m);
    
    for i=1:m
       for j=1:m
          if(j!=i)
            A(i) = A(i)*(x_vals(i)-x_vals(j));
          endif
       endfor 
       A(i)=1/A(i);    
    endfor
   
    p_numerator = zeros(1,length(x));
    p_denominator = zeros(1,length(x));
    
    for i=1:m
      inc = A(i)./(x-x_vals(i));
      p_numerator = p_numerator+inc.*f_vals(i);
      p_denominator = p_denominator+inc;
    endfor
     
  retval = p_numerator./p_denominator;
endfunction

