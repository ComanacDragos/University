pkg load optim

function r = aux(x)
  t = [0 3 5 8 13];
  d = [0 225 383 623 993];
  s = [75 77 80 74 72];
  r = hermite(x, t,d,s);
endfunction

position = aux(10)

speed = deriv(@aux, 10)