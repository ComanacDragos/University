pkg load statistics;

n = 10000;

T1 = exprnd(5, 1, n);

T2 = unifrnd(4, 6, 1, n);

T = 0.4*T1 + 0.6*T2;

m = mean(T);
s = std(T);
printf("Val medie:%d\nDeviatia standard:%d\n\n", m, s);

greater_than_5 = 0;
for i=1:n
  if T(i) > 5
    greater_than_5 += 1;
  endif
endfor

p = greater_than_5/n;
printf("Prob ca timp > 5 sec:%d\n\n", p);


greater_than_5 = 0;
for i=1:n
  if T2(i) > 5
    greater_than_5 += 1;
  endif
endfor
greater_than_5/n
printf("c) %d\n\n", ((greater_than_5/n)*0.6)/p);
