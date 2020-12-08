function X = geo_random (p, N)
  X = ones(1, N);
  for i=1:N
    while rand() >= p
      X(i) += 1; 
    endwhile
  endfor
endfunction
