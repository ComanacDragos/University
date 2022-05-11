1;
function [sol, nr]=jacobi(A, b, initial, precision, N)
  prev = initial;
  n=length(initial);
  for k=1:N
    current = zeros(length(initial), 1);
    for i=1:n
      s = 0;
      for j=1:n
        if j!=i
          s  = s + A(i, j) * prev(j);          
        endif
       endfor
      current(i) = (b(i) - s)/A(i,i);
    endfor
    
    error = norm(current-prev);
    
    if error < precision
      sol = current;
      nr = k;
      return
    endif
    prev = current;
  endfor
  message = "A solution could not have been found"
  sol = initial;
  nr = -1;
endfunction

function [sol, nr]=gauss_siedel(A, b, initial, precision, N)
  prev = initial;
  n=length(initial);
  for k=1:N
    current = zeros(length(initial), 1);
    for i=1:n
      s_left = 0;
      for j=1:i-1
          s_left = s_left + A(i, j) * current(j);          
       endfor
      s_right = 0;
      for j=i+1:n
          s_right = s_right + A(i, j) * prev(j);          
       endfor
      current(i) = (b(i) - s_left - s_right)/A(i,i);
    endfor
    
    error = norm(current-prev);
    
    if error < precision
      sol = current;
      nr = k;
      return
    endif
    prev = current;
  endfor
  message = "A solution could not have been found"
  sol = initial;
  nr = -1;
endfunction


function [sol, nr]=SOR(A, b, initial, precision, N, omega)
  if omega<=0 || omega >=2
     message = "Omega must be between 0 and 2"
    sol = initial;
    nr = -1;
  endif
  prev = initial;
  n=length(initial);
  for k=1:N
    current = zeros(length(initial), 1);
    for i=1:n
      s_left = 0;
      for j=1:i-1
          s_left = s_left + A(i, j) * current(j);          
       endfor
      s_right = 0;
      for j=i+1:n
          s_right = s_right + A(i, j) * prev(j);          
       endfor
      current(i) = omega*(b(i) - s_left - s_right)/A(i,i) + (1-omega)*prev(i);
    endfor
    
    error = norm(current-prev);
    
    if error < precision
      sol = current;
      nr = k;
      return
    endif
    prev = current;
  endfor
  message = "A solution could not have been found"
  sol = initial;
  nr = -1;
endfunction


A = [
3 -1 0 0 0 0;
-1 3 -1 0 0 0;
0 -1 3 -1 0 0;
0 0 -1 3 -1 0;
0 0 0 -1 3 -1;
0 0 0 0 -1 3;
];

b = [2;1;1;1;1;2];
initial = zeros(length(b),1);


true = A\b

[j_sol, j_nr] = jacobi(A, b, initial, 1e-3, 100)

[gs_sol, gs_nr] = gauss_siedel(A, b, initial, 1e-3, 100)

omega = 0.7;
[SOR_sol, SOR_nr] = SOR(A, b, initial, 1e-3, 100, omega)
