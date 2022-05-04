1;

function x=gauss(A, b)
  M = [A b];
  lines = length(M(:, 1));
  
  for line=1:lines
    [pivot, pivot_line] = max(abs(M(line:end, line)));    
    pivot_line = pivot_line + line-1;
    
    if line != pivot_line
      aux = M(line, :);
      M(line, :) = M(pivot_line, :);
      M(pivot_line, :) = aux;
    endif
    start_line = line+1;
    for change_line=start_line:lines
      M(change_line, :) = M(change_line, :) - M(change_line, line)/M(line,line) .* M(line, :); 
    endfor
  endfor
    
  x = zeros(1, line);
  
  x(lines) = M(end, end)/M(end, end-1);
  for line=lines-1:-1:1
    x(line) = (M(line, end) - sum(M(line, line+1:lines).*x(line+1:lines)))/M(line, line);    
  endfor
  x = x';
endfunction

A = [1 1 1 1;
2 3 1 5;
-1 1 -5 3;
3 1 7 -2;];
b = [10;31;-2;18];


%A = [1 1 -1; 1 1 4; 2 -1 2];
%b = [1;2;3];
computed = gauss(A, b)

real = A\b