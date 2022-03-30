pkg load optim;
function retval=aux(x)
  t = [0 3 5 8 13];
  d = [0 225 383 623 993];
  s = [75 77 80 74 72];
  retval = spline(t, [s(1), d, s(end)], x);
endfunction


position = aux(10)
speed = deriv(@aux, 10)