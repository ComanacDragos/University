
for n=10:15
  n
  k=1:n;
  t = 1./k;
  cond_nr = cond(fliplr(vander(t)))
endfor

