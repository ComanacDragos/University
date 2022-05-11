1;
function [sol, nr]=jacobi(A, b, initial, precision, N)
  prev = initial;
  n=length(initial);
  for k=1:N
    D = diag(diag(A));
    L = tril(A, -1);
    U = triu(A, 1);
   
    right = -(L+U)*prev + b;
   
    current = D\right; 
    
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
    D = diag(diag(A));
    L = tril(A, -1);
    U = triu(A, 1);
   
    left = D+L; 
    right = -U*prev + b;
   
    current = left\right; 
    
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
    D = diag(diag(A));
    L = tril(A, -1);
    U = triu(A, 1);
   
    left = D+omega*L; 
    right = ((1-omega)*D - omega*U)*prev + omega*b;
   
    current = left\right; 
    
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
3 1 1;
-2 4 0;
-1 2 -6;
];

b = [12;2;-5];
initial = zeros(length(b),1);


true = A\b

[j_sol, j_nr] = jacobi(A, b, initial, 1e-5, 100)

[gs_sol, gs_nr] = gauss_siedel(A, b, initial, 1e-5, 100)

omega = 0.7;
[SOR_sol, SOR_nr] = SOR(A, b, initial, 1e-5, 100, omega)
